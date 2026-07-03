/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeTypes.h"
#include "ATicTacToeGameMode.generated.h"

UCLASS()
class TICTACTO_AI_API ATicTacToeGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATicTacToeGameMode();

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    TArray<ETileState> Board;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    ETileState CurrentPlayer;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    bool bGameOver;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    ETileState Winner;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    ETicTacToePlayMode PlayMode;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    ETicTacToeControllerType XController;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    ETicTacToeControllerType OController;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe|RL")
    ETicTacToeRLAgentSlot XRLAgentSlot;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe|RL")
    ETicTacToeRLAgentSlot ORLAgentSlot;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    bool MakeMove(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void ResetGame();

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    ETileState GetTileState(int32 Index) const;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    FString GetTileText(int32 Index) const;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    FString GetStatusText() const;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void SetPlayMode(ETicTacToePlayMode NewPlayMode);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    ETicTacToePlayMode GetPlayMode() const;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void SetPlayerVsPlayer();

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void SetPlayerVsAI(ETileState HumanSide, ETicTacToeAIType AIType);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void SetAIVsAI(ETicTacToeAIType XAIType, ETicTacToeAIType OAIType);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void StartConfiguredMatch(ETicTacToeControllerType NewXController, ETicTacToeControllerType NewOController, ETicTacToeRLAgentSlot NewXRLAgentSlot, ETicTacToeRLAgentSlot NewORLAgentSlot);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe|RL")
    bool StartRLTrainingPlaceholder(ETicTacToeControllerType NewXController, ETicTacToeControllerType NewOController, ETicTacToeRLAgentSlot NewXRLAgentSlot, ETicTacToeRLAgentSlot NewORLAgentSlot, FTicTacToeRLTrainingSettings TrainingSettings);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    ETicTacToeControllerType GetControllerForPlayer(ETileState Player) const;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    bool IsPlayerAI(ETileState Player) const;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    FString GetPlayerLabel(ETileState Player) const;

private:
    bool MakeMoveForCurrentPlayer(int32 Index);
    void ContinueAIMoveChain();
    bool MakeAIMoveForCurrentPlayer();
    bool MakeRandomAIMove();
    bool MakeAlphaBetaAIMove();
    bool MakeReinforcementLearningAIMove();
    bool IsCurrentPlayerAI() const;
    void UpdatePlayModeFromControllers();
    ETicTacToeControllerType GetAIControllerType(ETicTacToeAIType AIType) const;
    FString GetControllerLabel(ETicTacToeControllerType ControllerType) const;
    FString GetRLAgentSaveSlotName(ETicTacToeRLAgentSlot AgentSlot) const;
    void SwitchTurn();
};
