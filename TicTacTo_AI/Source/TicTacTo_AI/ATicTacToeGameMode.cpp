/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "ATicTacToeGameMode.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
    PlayMode = ETicTacToePlayMode::PlayerVsPlayer;
    ResetGame();
}

void ATicTacToeGameMode::ResetGame()
{
    Board.Empty();
    Board.SetNum(9);

    for (int32 i = 0; i < Board.Num(); i++)
    {
        Board[i] = ETileState::Empty;
    }

    CurrentPlayer = ETileState::X;
    Winner = ETileState::Empty;
    bGameOver = false;
}

bool ATicTacToeGameMode::MakeMove(int32 Index)
{
    if (IsAIMode() && CurrentPlayer == ETileState::O)
    {
        return false;
    }

    const bool bMoveMade = MakeMoveForCurrentPlayer(Index);

    if (bMoveMade && IsAIMode() && !bGameOver && CurrentPlayer == ETileState::O)
    {
        if (PlayMode == ETicTacToePlayMode::PlayerVsAlphaBetaAI)
        {
            MakeAlphaBetaAIMove();
        }
        else if (PlayMode == ETicTacToePlayMode::PlayerVsReinforcementLearningAI)
        {
            MakeReinforcementLearningAIMove();
        }
        else
        {
            MakeRandomAIMove();
        }
    }

    return bMoveMade;
}

bool ATicTacToeGameMode::MakeMoveForCurrentPlayer(int32 Index)
{
    if (bGameOver)
    {
        return false;
    }

    if (!Board.IsValidIndex(Index))
    {
        return false;
    }

    if (Board[Index] != ETileState::Empty)
    {
        return false;
    }

    Board[Index] = CurrentPlayer;

    if (CheckWinner(CurrentPlayer))
    {
        Winner = CurrentPlayer;
        bGameOver = true;
        return true;
    }

    if (CheckDraw())
    {
        Winner = ETileState::Empty;
        bGameOver = true;
        return true;
    }

    SwitchTurn();
    return true;
}

ETileState ATicTacToeGameMode::GetTileState(int32 Index) const
{
    if (!Board.IsValidIndex(Index))
    {
        return ETileState::Empty;
    }

    return Board[Index];
}

FString ATicTacToeGameMode::GetTileText(int32 Index) const
{
    switch (GetTileState(Index))
    {
    case ETileState::X:
        return TEXT("X");
    case ETileState::O:
        return TEXT("O");
    case ETileState::Empty:
    default:
        return TEXT("");
    }
}

FString ATicTacToeGameMode::GetStatusText() const
{
    if (bGameOver)
    {
        if (Winner == ETileState::X)
        {
            return TEXT("X Wins!");
        }

        if (Winner == ETileState::O)
        {
            if (IsAIMode())
            {
                return TEXT("AI Wins!");
            }

            return TEXT("O Wins!");
        }

        return TEXT("Draw!");
    }

    if (IsAIMode())
    {
        return CurrentPlayer == ETileState::X ? TEXT("Your Turn") : TEXT("AI's Turn");
    }

    return CurrentPlayer == ETileState::X ? TEXT("X's Turn") : TEXT("O's Turn");
}

void ATicTacToeGameMode::SetPlayMode(ETicTacToePlayMode NewPlayMode)
{
    PlayMode = NewPlayMode;
    ResetGame();
}

ETicTacToePlayMode ATicTacToeGameMode::GetPlayMode() const
{
    return PlayMode;
}

void ATicTacToeGameMode::MakeRandomAIMove()
{
    TArray<int32> EmptyTiles;

    for (int32 Index = 0; Index < Board.Num(); ++Index)
    {
        if (Board[Index] == ETileState::Empty)
        {
            EmptyTiles.Add(Index);
        }
    }

    if (EmptyTiles.Num() == 0)
    {
        return;
    }

    const int32 RandomTileIndex = FMath::RandRange(0, EmptyTiles.Num() - 1);
    MakeMoveForCurrentPlayer(EmptyTiles[RandomTileIndex]);
}

void ATicTacToeGameMode::MakeAlphaBetaAIMove()
{
    int32 BestScore = TNumericLimits<int32>::Min();
    int32 BestMove = INDEX_NONE;

    for (int32 Index = 0; Index < Board.Num(); ++Index)
    {
        if (Board[Index] != ETileState::Empty)
        {
            continue;
        }

        Board[Index] = ETileState::O;
        const int32 MoveScore = Minimax(false, 0, TNumericLimits<int32>::Min(), TNumericLimits<int32>::Max());
        Board[Index] = ETileState::Empty;

        if (MoveScore > BestScore)
        {
            BestScore = MoveScore;
            BestMove = Index;
        }
    }

    if (BestMove != INDEX_NONE)
    {
        MakeMoveForCurrentPlayer(BestMove);
    }
}

bool ATicTacToeGameMode::IsAIMode() const
{
    return PlayMode == ETicTacToePlayMode::PlayerVsRandomAI
        || PlayMode == ETicTacToePlayMode::PlayerVsAlphaBetaAI
        || PlayMode == ETicTacToePlayMode::PlayerVsReinforcementLearningAI;
}

void ATicTacToeGameMode::MakeReinforcementLearningAIMove()
{
    MakeRandomAIMove();
}

int32 ATicTacToeGameMode::Minimax(bool bIsMaximizing, int32 Depth, int32 Alpha, int32 Beta)
{
    if (CheckWinner(ETileState::O))
    {
        return 10 - Depth;
    }

    if (CheckWinner(ETileState::X))
    {
        return Depth - 10;
    }

    if (CheckDraw())
    {
        return 0;
    }

    if (bIsMaximizing)
    {
        int32 BestScore = TNumericLimits<int32>::Min();

        for (int32 Index = 0; Index < Board.Num(); ++Index)
        {
            if (Board[Index] != ETileState::Empty)
            {
                continue;
            }

            Board[Index] = ETileState::O;
            BestScore = FMath::Max(BestScore, Minimax(false, Depth + 1, Alpha, Beta));
            Board[Index] = ETileState::Empty;

            Alpha = FMath::Max(Alpha, BestScore);
            if (Beta <= Alpha)
            {
                break;
            }
        }

        return BestScore;
    }

    int32 BestScore = TNumericLimits<int32>::Max();

    for (int32 Index = 0; Index < Board.Num(); ++Index)
    {
        if (Board[Index] != ETileState::Empty)
        {
            continue;
        }

        Board[Index] = ETileState::X;
        BestScore = FMath::Min(BestScore, Minimax(true, Depth + 1, Alpha, Beta));
        Board[Index] = ETileState::Empty;

        Beta = FMath::Min(Beta, BestScore);
        if (Beta <= Alpha)
        {
            break;
        }
    }

    return BestScore;
}

void ATicTacToeGameMode::SwitchTurn()
{
    CurrentPlayer = CurrentPlayer == ETileState::X ? ETileState::O : ETileState::X;
}

bool ATicTacToeGameMode::CheckWinner(ETileState Player) const
{
    const int32 WinPatterns[8][3] =
    {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},

        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},

        {0, 4, 8},
        {2, 4, 6}
    };

    for (int32 i = 0; i < 8; i++)
    {
        const int32 A = WinPatterns[i][0];
        const int32 B = WinPatterns[i][1];
        const int32 C = WinPatterns[i][2];

        if (Board[A] == Player && Board[B] == Player && Board[C] == Player)
        {
            return true;
        }
    }

    return false;
}

bool ATicTacToeGameMode::CheckDraw() const
{
    for (ETileState Tile : Board)
    {
        if (Tile == ETileState::Empty)
        {
            return false;
        }
    }

    return true;
}
