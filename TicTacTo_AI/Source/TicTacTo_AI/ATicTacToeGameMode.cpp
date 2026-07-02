/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "ATicTacToeGameMode.h"

#include "TicTacToeAlphaBetaAI.h"
#include "TicTacToeRules.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
    PlayMode = ETicTacToePlayMode::PlayerVsPlayer;
    ResetGame();
}

void ATicTacToeGameMode::ResetGame()
{
    FTicTacToeRules::InitializeBoard(Board);
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

    if (!FTicTacToeRules::IsValidMove(Board, Index))
    {
        return false;
    }

    Board[Index] = CurrentPlayer;

    if (FTicTacToeRules::CheckWinner(Board, CurrentPlayer))
    {
        Winner = CurrentPlayer;
        bGameOver = true;
        return true;
    }

    if (FTicTacToeRules::CheckDraw(Board))
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
    return FTicTacToeRules::GetTileText(Board, Index);
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
    FTicTacToeRules::GetAvailableMoves(Board, EmptyTiles);

    if (EmptyTiles.Num() == 0)
    {
        return;
    }

    const int32 RandomTileIndex = FMath::RandRange(0, EmptyTiles.Num() - 1);
    MakeMoveForCurrentPlayer(EmptyTiles[RandomTileIndex]);
}

void ATicTacToeGameMode::MakeAlphaBetaAIMove()
{
    const int32 BestMove = FTicTacToeAlphaBetaAI::FindBestMove(Board);

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

void ATicTacToeGameMode::SwitchTurn()
{
    CurrentPlayer = CurrentPlayer == ETileState::X ? ETileState::O : ETileState::X;
}
