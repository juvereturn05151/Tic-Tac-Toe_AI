/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "TicTacToeRLTrainingManager.h"

#include "TicTacToeQLearningAgent.h"
#include "TicTacToeRules.h"

namespace
{
FString MakeAgentName(const FString& SaveSlotName)
{
    return SaveSlotName.IsEmpty() ? TEXT("TicTacToeRLAgent") : FString::Printf(TEXT("TicTacToeRLAgent_%s"), *SaveSlotName);
}
}

void UTicTacToeRLTrainingManager::SetTrainingSettings(FTicTacToeRLTrainingSettings NewTrainingSettings)
{
    TrainingSettings.EpisodeCount = FMath::Max(1, NewTrainingSettings.EpisodeCount);
    TrainingSettings.LearningRate = FMath::Clamp(NewTrainingSettings.LearningRate, 0.0f, 1.0f);
    TrainingSettings.DiscountFactor = FMath::Clamp(NewTrainingSettings.DiscountFactor, 0.0f, 1.0f);
    TrainingSettings.ExplorationRate = FMath::Clamp(NewTrainingSettings.ExplorationRate, 0.0f, 1.0f);
}

FTicTacToeRLTrainingStats UTicTacToeRLTrainingManager::TrainAgentVsRandom(int32 EpisodeCount, const FString& SaveSlotName)
{
    FTicTacToeRLTrainingStats PreviousStats;
    FTicTacToeRLTrainingStats RunStats;
    FTicTacToeQLearningAgent Agent;
    Agent.SetTrainingSettings(TrainingSettings);
    Agent.LoadAgent(SaveSlotName, &PreviousStats);
    Agent.SetTrainingSettings(TrainingSettings);

    const int32 ClampedEpisodeCount = FMath::Max(1, EpisodeCount);
    constexpr ETileState RLPlayer = ETileState::X;
    constexpr ETileState RandomPlayer = ETileState::O;

    for (int32 EpisodeIndex = 0; EpisodeIndex < ClampedEpisodeCount; ++EpisodeIndex)
    {
        TArray<ETileState> Board;
        FTicTacToeRules::InitializeBoard(Board);

        bool bEpisodeDone = false;
        while (!bEpisodeDone)
        {
            const TArray<ETileState> StateBeforeAction = Board;
            const int32 RLMove = Agent.ChooseAction(Board, true);

            if (!ApplyMove(Board, RLMove, RLPlayer))
            {
                Agent.Learn(StateBeforeAction, RLMove, FTicTacToeQLearningAgent::InvalidMoveReward, Board, true);
                ++RunStats.RLLosses;
                bEpisodeDone = true;
                break;
            }

            float Reward = FTicTacToeQLearningAgent::NormalMoveReward;
            if (IsTerminal(Board, RLPlayer, Reward, RunStats))
            {
                Agent.Learn(StateBeforeAction, RLMove, Reward, Board, true);
                bEpisodeDone = true;
                break;
            }

            const int32 RandomMove = ChooseRandomMove(Board);
            ApplyMove(Board, RandomMove, RandomPlayer);

            if (IsTerminal(Board, RLPlayer, Reward, RunStats))
            {
                Agent.Learn(StateBeforeAction, RLMove, Reward, Board, true);
                bEpisodeDone = true;
                break;
            }

            Agent.Learn(StateBeforeAction, RLMove, FTicTacToeQLearningAgent::NormalMoveReward, Board, false);
        }
    }

    RunStats.TotalEpisodes = ClampedEpisodeCount;
    RunStats.Recalculate();

    FTicTacToeRLTrainingStats SavedStats = RunStats;
    SavedStats.TotalEpisodes += PreviousStats.TotalEpisodes;
    SavedStats.RLWins += PreviousStats.RLWins;
    SavedStats.RLLosses += PreviousStats.RLLosses;
    SavedStats.Draws += PreviousStats.Draws;
    SavedStats.Recalculate();

    const bool bSaved = Agent.SaveAgent(SaveSlotName, MakeAgentName(SaveSlotName), SavedStats);

    UE_LOG(LogTemp, Display, TEXT("RL training vs Random complete. Slot=%s Episodes=%d Wins=%d Losses=%d Draws=%d WinRate=%.2f%% KnownStates=%d Saved=%s"),
        *SaveSlotName,
        RunStats.TotalEpisodes,
        RunStats.RLWins,
        RunStats.RLLosses,
        RunStats.Draws,
        RunStats.WinRate * 100.0f,
        Agent.GetKnownStateCount(),
        bSaved ? TEXT("true") : TEXT("false"));

    UE_LOG(LogTemp, Display, TEXT("RL cumulative stats. Slot=%s TotalEpisodes=%d Wins=%d Losses=%d Draws=%d WinRate=%.2f%%"),
        *SaveSlotName,
        SavedStats.TotalEpisodes,
        SavedStats.RLWins,
        SavedStats.RLLosses,
        SavedStats.Draws,
        SavedStats.WinRate * 100.0f);

    // Future training hooks:
    // - RL vs AlphaBeta: replace RandomPlayer move selection with FTicTacToeAlphaBetaAI::FindBestMove.
    // - RL vs RL self-play: maintain two FTicTacToeQLearningAgent instances and update both after each turn.
    // - Multiple saved RL slots: pass the UI-selected slot names into this manager for each RL side.
    // - Play mode inference: load the selected saved agent and call ChooseAction(Board, false).
    return RunStats;
}

int32 UTicTacToeRLTrainingManager::ChooseRandomMove(const TArray<ETileState>& Board) const
{
    TArray<int32> AvailableMoves;
    FTicTacToeRules::GetAvailableMoves(Board, AvailableMoves);

    if (AvailableMoves.Num() == 0)
    {
        return INDEX_NONE;
    }

    return AvailableMoves[FMath::RandRange(0, AvailableMoves.Num() - 1)];
}

bool UTicTacToeRLTrainingManager::ApplyMove(TArray<ETileState>& Board, int32 Move, ETileState Player) const
{
    if (!FTicTacToeRules::IsValidMove(Board, Move))
    {
        return false;
    }

    Board[Move] = Player;
    return true;
}

bool UTicTacToeRLTrainingManager::IsTerminal(const TArray<ETileState>& Board, ETileState RLPlayer, float& OutReward, FTicTacToeRLTrainingStats& InOutStats) const
{
    const ETileState OpponentPlayer = RLPlayer == ETileState::X ? ETileState::O : ETileState::X;

    if (FTicTacToeRules::CheckWinner(Board, RLPlayer))
    {
        OutReward = FTicTacToeQLearningAgent::WinReward;
        ++InOutStats.RLWins;
        return true;
    }

    if (FTicTacToeRules::CheckWinner(Board, OpponentPlayer))
    {
        OutReward = FTicTacToeQLearningAgent::LoseReward;
        ++InOutStats.RLLosses;
        return true;
    }

    if (FTicTacToeRules::CheckDraw(Board))
    {
        OutReward = FTicTacToeQLearningAgent::DrawReward;
        ++InOutStats.Draws;
        return true;
    }

    OutReward = FTicTacToeQLearningAgent::NormalMoveReward;
    return false;
}
