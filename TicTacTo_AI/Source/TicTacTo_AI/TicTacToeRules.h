/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "TicTacToeTypes.h"

class TICTACTO_AI_API FTicTacToeRules
{
public:
    static void InitializeBoard(TArray<ETileState>& Board);
    static bool IsValidMove(const TArray<ETileState>& Board, int32 Index);
    static void GetAvailableMoves(const TArray<ETileState>& Board, TArray<int32>& OutMoves);
    static bool CheckWinner(const TArray<ETileState>& Board, ETileState Player);
    static bool CheckDraw(const TArray<ETileState>& Board);
    static FString GetBoardStateKey(const TArray<ETileState>& Board);
    static FString GetTileText(const TArray<ETileState>& Board, int32 Index);
};
