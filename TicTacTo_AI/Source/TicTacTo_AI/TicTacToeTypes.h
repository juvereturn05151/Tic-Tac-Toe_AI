/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "TicTacToeTypes.generated.h"

UENUM(BlueprintType)
enum class ETileState : uint8
{
    Empty UMETA(DisplayName = "Empty"),
    X     UMETA(DisplayName = "X"),
    O     UMETA(DisplayName = "O")
};

UENUM(BlueprintType)
enum class ETicTacToePlayMode : uint8
{
    PlayerVsPlayer                  UMETA(DisplayName = "Player vs Player"),
    PlayerVsRandomAI                UMETA(DisplayName = "Player vs AI (Random)"),
    PlayerVsAlphaBetaAI             UMETA(DisplayName = "Player vs AI (Alpha-Beta)"),
    PlayerVsReinforcementLearningAI UMETA(DisplayName = "Player vs AI (Reinforcement Learning)")
};
