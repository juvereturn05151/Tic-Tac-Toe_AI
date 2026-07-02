/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "TicTacToeAlphaBetaAI.h"

#include "AlphaBetaSearch.h"
#include "TicTacToeRules.h"

namespace
{
struct FTicTacToeAlphaBetaAdapter
{
    ETileState AIPlayer = ETileState::O;
    ETileState HumanPlayer = ETileState::X;

    int32 GetInvalidMove() const
    {
        return INDEX_NONE;
    }

    void GetAvailableMoves(const TArray<ETileState>& Board, TArray<int32>& OutMoves) const
    {
        FTicTacToeRules::GetAvailableMoves(Board, OutMoves);
    }

    void ApplyMove(TArray<ETileState>& Board, int32 Move, bool bIsMaximizing) const
    {
        if (Board.IsValidIndex(Move))
        {
            Board[Move] = bIsMaximizing ? AIPlayer : HumanPlayer;
        }
    }

    void UndoMove(TArray<ETileState>& Board, int32 Move) const
    {
        if (Board.IsValidIndex(Move))
        {
            Board[Move] = ETileState::Empty;
        }
    }

    bool IsTerminal(const TArray<ETileState>& Board, int32 Depth, int32& OutScore) const
    {
        if (FTicTacToeRules::CheckWinner(Board, AIPlayer))
        {
            OutScore = 10 - Depth;
            return true;
        }

        if (FTicTacToeRules::CheckWinner(Board, HumanPlayer))
        {
            OutScore = Depth - 10;
            return true;
        }

        if (FTicTacToeRules::CheckDraw(Board))
        {
            OutScore = 0;
            return true;
        }

        return false;
    }

    int32 Evaluate(const TArray<ETileState>& Board, int32 Depth) const
    {
        int32 Score = 0;
        IsTerminal(Board, Depth, Score);
        return Score;
    }
};
}

int32 FTicTacToeAlphaBetaAI::FindBestMove(const TArray<ETileState>& Board, ETileState AIPlayer, ETileState HumanPlayer)
{
    const FTicTacToeAlphaBetaAdapter Adapter{AIPlayer, HumanPlayer};
    return TAlphaBetaSearch<TArray<ETileState>, int32, FTicTacToeAlphaBetaAdapter>::FindBestMove(Board, Adapter);
}
