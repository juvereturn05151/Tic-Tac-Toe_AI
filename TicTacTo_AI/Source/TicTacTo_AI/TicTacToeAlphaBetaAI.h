/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "TicTacToeTypes.h"

class TICTACTO_AI_API FTicTacToeAlphaBetaAI
{
public:
    static int32 FindBestMove(const TArray<ETileState>& Board, ETileState AIPlayer = ETileState::O, ETileState HumanPlayer = ETileState::X);
};
