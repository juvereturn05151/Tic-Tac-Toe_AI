/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "TicTacToeTypes.h"

class TICTACTO_AI_API FTicTacToeQLearningAgent
{
public:
    static constexpr float WinReward = 1.0f;
    static constexpr float DrawReward = 0.2f;
    static constexpr float LoseReward = -1.0f;
    static constexpr float NormalMoveReward = 0.0f;
    static constexpr float InvalidMoveReward = -1.0f;

    FTicTacToeQLearningAgent();

    int32 ChooseAction(const TArray<ETileState>& Board, bool bAllowExploration = true);
    void Learn(const TArray<ETileState>& CurrentBoard, int32 Action, float Reward, const TArray<ETileState>& NextBoard, bool bNextStateIsTerminal);

    void ResetTrainingSettings();
    void SetTrainingSettings(const FTicTacToeRLTrainingSettings& NewTrainingSettings);

    bool SaveAgent(const FString& SaveSlotName, const FString& AgentName, const FTicTacToeRLTrainingStats& TrainingStats) const;
    bool LoadAgent(const FString& SaveSlotName, FTicTacToeRLTrainingStats* OutTrainingStats = nullptr);

    const TMap<FString, TArray<float>>& GetQTable() const;
    int32 GetKnownStateCount() const;

private:
    TArray<float>& GetOrCreateQValues(const FString& StateKey);
    float GetMaxQValueForLegalMoves(const TArray<ETileState>& Board);
    int32 ChooseRandomAction(const TArray<int32>& AvailableMoves) const;
    int32 ChooseBestKnownAction(const FString& StateKey, const TArray<int32>& AvailableMoves);

    TMap<FString, TArray<float>> QTable;
    FTicTacToeRLTrainingSettings TrainingSettings;
};
