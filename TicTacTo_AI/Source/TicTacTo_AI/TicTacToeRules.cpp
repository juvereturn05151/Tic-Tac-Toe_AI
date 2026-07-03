/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "TicTacToeRules.h"

void FTicTacToeRules::InitializeBoard(TArray<ETileState>& Board)
{
    Board.Empty();
    Board.SetNum(9);

    for (ETileState& Tile : Board)
    {
        Tile = ETileState::Empty;
    }
}

bool FTicTacToeRules::IsValidMove(const TArray<ETileState>& Board, int32 Index)
{
    return Board.IsValidIndex(Index) && Board[Index] == ETileState::Empty;
}

void FTicTacToeRules::GetAvailableMoves(const TArray<ETileState>& Board, TArray<int32>& OutMoves)
{
    OutMoves.Reset();

    for (int32 Index = 0; Index < Board.Num(); ++Index)
    {
        if (Board[Index] == ETileState::Empty)
        {
            OutMoves.Add(Index);
        }
    }
}

bool FTicTacToeRules::CheckWinner(const TArray<ETileState>& Board, ETileState Player)
{
    if (Board.Num() < 9)
    {
        return false;
    }

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

bool FTicTacToeRules::CheckDraw(const TArray<ETileState>& Board)
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

FString FTicTacToeRules::GetBoardStateKey(const TArray<ETileState>& Board)
{
    FString StateKey;
    StateKey.Reserve(9);

    for (int32 Index = 0; Index < 9; ++Index)
    {
        const ETileState Tile = Board.IsValidIndex(Index) ? Board[Index] : ETileState::Empty;

        if (Tile == ETileState::X)
        {
            StateKey.AppendChar(TEXT('X'));
        }
        else if (Tile == ETileState::O)
        {
            StateKey.AppendChar(TEXT('O'));
        }
        else
        {
            StateKey.AppendChar(TEXT('_'));
        }
    }

    return StateKey;
}

FString FTicTacToeRules::GetTileText(const TArray<ETileState>& Board, int32 Index)
{
    if (!Board.IsValidIndex(Index))
    {
        return TEXT("");
    }

    switch (Board[Index])
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
