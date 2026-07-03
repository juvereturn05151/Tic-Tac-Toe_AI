/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "TicTacToeQLearningAgent.h"

#include "Kismet/GameplayStatics.h"
#include "TicTacToeRLSaveGame.h"
#include "TicTacToeRules.h"

namespace
{
constexpr int32 BoardTileCount = 9;
constexpr int32 SaveUserIndex = 0;

TArray<float> MakeDefaultQValues()
{
    TArray<float> Values;
    Values.Init(0.0f, BoardTileCount);
    return Values;
}
}

FTicTacToeQLearningAgent::FTicTacToeQLearningAgent()
{
    ResetTrainingSettings();
}

int32 FTicTacToeQLearningAgent::ChooseAction(const TArray<ETileState>& Board, bool bAllowExploration)
{
    TArray<int32> AvailableMoves;
    FTicTacToeRules::GetAvailableMoves(Board, AvailableMoves);

    if (AvailableMoves.Num() == 0)
    {
        return INDEX_NONE;
    }

    const FString StateKey = FTicTacToeRules::GetBoardStateKey(Board);
    GetOrCreateQValues(StateKey);

    if (bAllowExploration && FMath::FRand() < TrainingSettings.ExplorationRate)
    {
        return ChooseRandomAction(AvailableMoves);
    }

    return ChooseBestKnownAction(StateKey, AvailableMoves);
}

void FTicTacToeQLearningAgent::Learn(const TArray<ETileState>& CurrentBoard, int32 Action, float Reward, const TArray<ETileState>& NextBoard, bool bNextStateIsTerminal)
{
    if (!CurrentBoard.IsValidIndex(Action))
    {
        Reward = InvalidMoveReward;
        return;
    }

    const FString CurrentStateKey = FTicTacToeRules::GetBoardStateKey(CurrentBoard);
    TArray<float>& CurrentQValues = GetOrCreateQValues(CurrentStateKey);

    if (!CurrentQValues.IsValidIndex(Action))
    {
        return;
    }

    const float CurrentQ = CurrentQValues[Action];
    const float NextMaxQ = bNextStateIsTerminal ? 0.0f : GetMaxQValueForLegalMoves(NextBoard);
    CurrentQValues[Action] = CurrentQ + TrainingSettings.LearningRate * (Reward + TrainingSettings.DiscountFactor * NextMaxQ - CurrentQ);
}

void FTicTacToeQLearningAgent::ResetTrainingSettings()
{
    TrainingSettings.EpisodeCount = 10000;
    TrainingSettings.LearningRate = 0.1f;
    TrainingSettings.DiscountFactor = 0.95f;
    TrainingSettings.ExplorationRate = 0.2f;
}

void FTicTacToeQLearningAgent::SetTrainingSettings(const FTicTacToeRLTrainingSettings& NewTrainingSettings)
{
    TrainingSettings.EpisodeCount = FMath::Max(1, NewTrainingSettings.EpisodeCount);
    TrainingSettings.LearningRate = FMath::Clamp(NewTrainingSettings.LearningRate, 0.0f, 1.0f);
    TrainingSettings.DiscountFactor = FMath::Clamp(NewTrainingSettings.DiscountFactor, 0.0f, 1.0f);
    TrainingSettings.ExplorationRate = FMath::Clamp(NewTrainingSettings.ExplorationRate, 0.0f, 1.0f);
}

bool FTicTacToeQLearningAgent::SaveAgent(const FString& SaveSlotName, const FString& AgentName, const FTicTacToeRLTrainingStats& TrainingStats) const
{
    if (SaveSlotName.IsEmpty())
    {
        return false;
    }

    UTicTacToeRLSaveGame* SaveGame = Cast<UTicTacToeRLSaveGame>(UGameplayStatics::CreateSaveGameObject(UTicTacToeRLSaveGame::StaticClass()));
    if (!SaveGame)
    {
        return false;
    }

    SaveGame->AgentName = AgentName;
    SaveGame->EpisodesTrained = TrainingStats.TotalEpisodes;
    SaveGame->TrainingStats = TrainingStats;
    SaveGame->TrainingSettings = TrainingSettings;

    for (const TPair<FString, TArray<float>>& Entry : QTable)
    {
        FTicTacToeQValueArray WrappedValues;
        WrappedValues.Values = Entry.Value;
        SaveGame->SavedQTable.Add(Entry.Key, WrappedValues);
    }

    return UGameplayStatics::SaveGameToSlot(SaveGame, SaveSlotName, SaveUserIndex);
}

bool FTicTacToeQLearningAgent::LoadAgent(const FString& SaveSlotName, FTicTacToeRLTrainingStats* OutTrainingStats)
{
    QTable.Reset();

    if (OutTrainingStats)
    {
        *OutTrainingStats = FTicTacToeRLTrainingStats();
    }

    if (SaveSlotName.IsEmpty() || !UGameplayStatics::DoesSaveGameExist(SaveSlotName, SaveUserIndex))
    {
        return false;
    }

    UTicTacToeRLSaveGame* SaveGame = Cast<UTicTacToeRLSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, SaveUserIndex));
    if (!SaveGame)
    {
        return false;
    }

    for (const TPair<FString, FTicTacToeQValueArray>& Entry : SaveGame->SavedQTable)
    {
        TArray<float> Values = Entry.Value.Values;
        Values.SetNum(BoardTileCount);
        QTable.Add(Entry.Key, Values);
    }

    TrainingSettings = SaveGame->TrainingSettings;

    if (OutTrainingStats)
    {
        *OutTrainingStats = SaveGame->TrainingStats;
    }

    return true;
}

const TMap<FString, TArray<float>>& FTicTacToeQLearningAgent::GetQTable() const
{
    return QTable;
}

int32 FTicTacToeQLearningAgent::GetKnownStateCount() const
{
    return QTable.Num();
}

TArray<float>& FTicTacToeQLearningAgent::GetOrCreateQValues(const FString& StateKey)
{
    if (TArray<float>* ExistingValues = QTable.Find(StateKey))
    {
        ExistingValues->SetNum(BoardTileCount);
        return *ExistingValues;
    }

    return QTable.Add(StateKey, MakeDefaultQValues());
}

float FTicTacToeQLearningAgent::GetMaxQValueForLegalMoves(const TArray<ETileState>& Board)
{
    TArray<int32> AvailableMoves;
    FTicTacToeRules::GetAvailableMoves(Board, AvailableMoves);

    if (AvailableMoves.Num() == 0)
    {
        return 0.0f;
    }

    const FString StateKey = FTicTacToeRules::GetBoardStateKey(Board);
    TArray<float>& QValues = GetOrCreateQValues(StateKey);

    float BestValue = TNumericLimits<float>::Lowest();
    for (int32 Move : AvailableMoves)
    {
        if (QValues.IsValidIndex(Move))
        {
            BestValue = FMath::Max(BestValue, QValues[Move]);
        }
    }

    return BestValue == TNumericLimits<float>::Lowest() ? 0.0f : BestValue;
}

int32 FTicTacToeQLearningAgent::ChooseRandomAction(const TArray<int32>& AvailableMoves) const
{
    if (AvailableMoves.Num() == 0)
    {
        return INDEX_NONE;
    }

    return AvailableMoves[FMath::RandRange(0, AvailableMoves.Num() - 1)];
}

int32 FTicTacToeQLearningAgent::ChooseBestKnownAction(const FString& StateKey, const TArray<int32>& AvailableMoves)
{
    if (AvailableMoves.Num() == 0)
    {
        return INDEX_NONE;
    }

    TArray<float>& QValues = GetOrCreateQValues(StateKey);
    float BestValue = TNumericLimits<float>::Lowest();
    TArray<int32> BestMoves;

    for (int32 Move : AvailableMoves)
    {
        if (!QValues.IsValidIndex(Move))
        {
            continue;
        }

        if (QValues[Move] > BestValue)
        {
            BestValue = QValues[Move];
            BestMoves.Reset();
            BestMoves.Add(Move);
        }
        else if (FMath::IsNearlyEqual(QValues[Move], BestValue))
        {
            BestMoves.Add(Move);
        }
    }

    return BestMoves.Num() > 0 ? ChooseRandomAction(BestMoves) : ChooseRandomAction(AvailableMoves);
}
