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
    PlayerVsReinforcementLearningAI UMETA(DisplayName = "Player vs AI (Reinforcement Learning)"),
    AIVsAI                          UMETA(DisplayName = "AI vs AI")
};

UENUM(BlueprintType)
enum class ETicTacToeMatchMode : uint8
{
    PlayerVsPlayer UMETA(DisplayName = "Player vs Player"),
    PlayerVsAI     UMETA(DisplayName = "Player vs AI"),
    AIVsAI         UMETA(DisplayName = "AI vs AI")
};

UENUM(BlueprintType)
enum class ETicTacToeAIType : uint8
{
    Random                 UMETA(DisplayName = "Random"),
    AlphaBeta              UMETA(DisplayName = "Alpha-Beta"),
    ReinforcementLearning  UMETA(DisplayName = "Reinforcement Learning")
};

UENUM(BlueprintType)
enum class ETicTacToeControllerType : uint8
{
    Human                  UMETA(DisplayName = "Human"),
    RandomAI               UMETA(DisplayName = "Random AI"),
    AlphaBetaAI            UMETA(DisplayName = "Alpha-Beta AI"),
    ReinforcementLearningAI UMETA(DisplayName = "Reinforcement Learning AI")
};

UENUM(BlueprintType)
enum class ETicTacToeRLAgentSlot : uint8
{
    Slot1 UMETA(DisplayName = "RL Agent Slot 1"),
    Slot2 UMETA(DisplayName = "RL Agent Slot 2"),
    Slot3 UMETA(DisplayName = "RL Agent Slot 3")
};

UENUM(BlueprintType)
enum class ETicTacToeMenuAction : uint8
{
    Play  UMETA(DisplayName = "Play"),
    Train UMETA(DisplayName = "Train")
};
