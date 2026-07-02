/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"

template <typename TGameState, typename TMove, typename TGameAdapter>
class TAlphaBetaSearch
{
public:
    static TMove FindBestMove(const TGameState& InitialState, const TGameAdapter& GameAdapter, bool bMaximizingPlayer = true, int32 MaxDepth = TNumericLimits<int32>::Max())
    {
        TArray<TMove> AvailableMoves;
        GameAdapter.GetAvailableMoves(InitialState, AvailableMoves);

        TMove BestMove = GameAdapter.GetInvalidMove();
        int32 BestScore = bMaximizingPlayer ? TNumericLimits<int32>::Min() : TNumericLimits<int32>::Max();
        TGameState TestState = InitialState;

        for (const TMove& Move : AvailableMoves)
        {
            GameAdapter.ApplyMove(TestState, Move, bMaximizingPlayer);
            const int32 MoveScore = Minimax(TestState, GameAdapter, !bMaximizingPlayer, 1, MaxDepth, TNumericLimits<int32>::Min(), TNumericLimits<int32>::Max());
            GameAdapter.UndoMove(TestState, Move);

            if ((bMaximizingPlayer && MoveScore > BestScore) || (!bMaximizingPlayer && MoveScore < BestScore))
            {
                BestScore = MoveScore;
                BestMove = Move;
            }
        }

        return BestMove;
    }

private:
    static int32 Minimax(TGameState& State, const TGameAdapter& GameAdapter, bool bIsMaximizing, int32 Depth, int32 MaxDepth, int32 Alpha, int32 Beta)
    {
        int32 TerminalScore = 0;
        if (GameAdapter.IsTerminal(State, Depth, TerminalScore))
        {
            return TerminalScore;
        }

        if (Depth >= MaxDepth)
        {
            return GameAdapter.Evaluate(State, Depth);
        }

        TArray<TMove> AvailableMoves;
        GameAdapter.GetAvailableMoves(State, AvailableMoves);

        if (bIsMaximizing)
        {
            int32 BestScore = TNumericLimits<int32>::Min();

            for (const TMove& Move : AvailableMoves)
            {
                GameAdapter.ApplyMove(State, Move, true);
                BestScore = FMath::Max(BestScore, Minimax(State, GameAdapter, false, Depth + 1, MaxDepth, Alpha, Beta));
                GameAdapter.UndoMove(State, Move);

                Alpha = FMath::Max(Alpha, BestScore);
                if (Beta <= Alpha)
                {
                    break;
                }
            }

            return BestScore;
        }

        int32 BestScore = TNumericLimits<int32>::Max();

        for (const TMove& Move : AvailableMoves)
        {
            GameAdapter.ApplyMove(State, Move, false);
            BestScore = FMath::Min(BestScore, Minimax(State, GameAdapter, true, Depth + 1, MaxDepth, Alpha, Beta));
            GameAdapter.UndoMove(State, Move);

            Beta = FMath::Min(Beta, BestScore);
            if (Beta <= Alpha)
            {
                break;
            }
        }

        return BestScore;
    }
};
