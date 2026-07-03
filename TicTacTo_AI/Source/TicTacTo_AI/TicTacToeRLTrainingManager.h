/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TicTacToeTypes.h"
#include "TicTacToeRLTrainingManager.generated.h"

UCLASS(BlueprintType)
class TICTACTO_AI_API UTicTacToeRLTrainingManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "TicTacToe|RL Training")
    void SetTrainingSettings(FTicTacToeRLTrainingSettings NewTrainingSettings);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe|RL Training")
    FTicTacToeRLTrainingStats TrainAgentVsRandom(int32 EpisodeCount, const FString& SaveSlotName);

private:
    int32 ChooseRandomMove(const TArray<ETileState>& Board) const;
    bool ApplyMove(TArray<ETileState>& Board, int32 Move, ETileState Player) const;
    bool IsTerminal(const TArray<ETileState>& Board, ETileState RLPlayer, float& OutReward, FTicTacToeRLTrainingStats& InOutStats) const;

    FTicTacToeRLTrainingSettings TrainingSettings;
};
