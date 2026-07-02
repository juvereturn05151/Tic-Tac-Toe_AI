/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "ATicTacToeGameMode.h"

#include "TicTacToeAlphaBetaAI.h"
#include "TicTacToeRules.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
    PlayMode = ETicTacToePlayMode::PlayerVsPlayer;
    XController = ETicTacToeControllerType::Human;
    OController = ETicTacToeControllerType::Human;
    XRLAgentSlot = ETicTacToeRLAgentSlot::Slot1;
    ORLAgentSlot = ETicTacToeRLAgentSlot::Slot1;
    ResetGame();
}

void ATicTacToeGameMode::ResetGame()
{
    FTicTacToeRules::InitializeBoard(Board);
    CurrentPlayer = ETileState::X;
    Winner = ETileState::Empty;
    bGameOver = false;
    ContinueAIMoveChain();
}

bool ATicTacToeGameMode::MakeMove(int32 Index)
{
    if (IsCurrentPlayerAI())
    {
        return false;
    }

    const bool bMoveMade = MakeMoveForCurrentPlayer(Index);

    if (bMoveMade)
    {
        ContinueAIMoveChain();
    }

    return bMoveMade;
}

bool ATicTacToeGameMode::MakeMoveForCurrentPlayer(int32 Index)
{
    if (bGameOver)
    {
        return false;
    }

    if (!FTicTacToeRules::IsValidMove(Board, Index))
    {
        return false;
    }

    Board[Index] = CurrentPlayer;

    if (FTicTacToeRules::CheckWinner(Board, CurrentPlayer))
    {
        Winner = CurrentPlayer;
        bGameOver = true;
        return true;
    }

    if (FTicTacToeRules::CheckDraw(Board))
    {
        Winner = ETileState::Empty;
        bGameOver = true;
        return true;
    }

    SwitchTurn();
    return true;
}

ETileState ATicTacToeGameMode::GetTileState(int32 Index) const
{
    if (!Board.IsValidIndex(Index))
    {
        return ETileState::Empty;
    }

    return Board[Index];
}

FString ATicTacToeGameMode::GetTileText(int32 Index) const
{
    return FTicTacToeRules::GetTileText(Board, Index);
}

FString ATicTacToeGameMode::GetStatusText() const
{
    if (bGameOver)
    {
        if (Winner == ETileState::X)
        {
            return FString::Printf(TEXT("%s Wins!"), *GetPlayerLabel(ETileState::X));
        }

        if (Winner == ETileState::O)
        {
            return FString::Printf(TEXT("%s Wins!"), *GetPlayerLabel(ETileState::O));
        }

        return TEXT("Draw!");
    }

    if (IsCurrentPlayerAI())
    {
        return FString::Printf(TEXT("%s's Turn"), *GetPlayerLabel(CurrentPlayer));
    }

    return FString::Printf(TEXT("%s's Turn"), *GetPlayerLabel(CurrentPlayer));
}

void ATicTacToeGameMode::SetPlayMode(ETicTacToePlayMode NewPlayMode)
{
    if (NewPlayMode == ETicTacToePlayMode::PlayerVsPlayer)
    {
        SetPlayerVsPlayer();
    }
    else if (NewPlayMode == ETicTacToePlayMode::PlayerVsAlphaBetaAI)
    {
        SetPlayerVsAI(ETileState::X, ETicTacToeAIType::AlphaBeta);
    }
    else if (NewPlayMode == ETicTacToePlayMode::PlayerVsReinforcementLearningAI)
    {
        SetPlayerVsAI(ETileState::X, ETicTacToeAIType::ReinforcementLearning);
    }
    else if (NewPlayMode == ETicTacToePlayMode::AIVsAI)
    {
        SetAIVsAI(ETicTacToeAIType::AlphaBeta, ETicTacToeAIType::AlphaBeta);
    }
    else
    {
        SetPlayerVsAI(ETileState::X, ETicTacToeAIType::Random);
    }
}

ETicTacToePlayMode ATicTacToeGameMode::GetPlayMode() const
{
    return PlayMode;
}

void ATicTacToeGameMode::SetPlayerVsPlayer()
{
    StartConfiguredMatch(ETicTacToeControllerType::Human, ETicTacToeControllerType::Human, XRLAgentSlot, ORLAgentSlot);
}

void ATicTacToeGameMode::SetPlayerVsAI(ETileState HumanSide, ETicTacToeAIType AIType)
{
    const ETileState NormalizedHumanSide = HumanSide == ETileState::O ? ETileState::O : ETileState::X;
    const ETicTacToeControllerType AIController = GetAIControllerType(AIType);

    XController = NormalizedHumanSide == ETileState::X ? ETicTacToeControllerType::Human : AIController;
    OController = NormalizedHumanSide == ETileState::O ? ETicTacToeControllerType::Human : AIController;

    StartConfiguredMatch(XController, OController, XRLAgentSlot, ORLAgentSlot);
}

void ATicTacToeGameMode::SetAIVsAI(ETicTacToeAIType XAIType, ETicTacToeAIType OAIType)
{
    StartConfiguredMatch(GetAIControllerType(XAIType), GetAIControllerType(OAIType), XRLAgentSlot, ORLAgentSlot);
}

void ATicTacToeGameMode::StartConfiguredMatch(ETicTacToeControllerType NewXController, ETicTacToeControllerType NewOController, ETicTacToeRLAgentSlot NewXRLAgentSlot, ETicTacToeRLAgentSlot NewORLAgentSlot)
{
    XController = NewXController;
    OController = NewOController;
    XRLAgentSlot = NewXRLAgentSlot;
    ORLAgentSlot = NewORLAgentSlot;

    // Future RL hook: load the selected saved agents before ResetGame().
    // XRLAgentSlot and ORLAgentSlot identify which saved policy/checkpoint each RL side should use.
    UpdatePlayModeFromControllers();
    ResetGame();
}

bool ATicTacToeGameMode::StartRLTrainingPlaceholder(ETicTacToeControllerType NewXController, ETicTacToeControllerType NewOController, ETicTacToeRLAgentSlot NewXRLAgentSlot, ETicTacToeRLAgentSlot NewORLAgentSlot)
{
    if (NewXController != ETicTacToeControllerType::ReinforcementLearningAI
        && NewOController != ETicTacToeControllerType::ReinforcementLearningAI)
    {
        return false;
    }

    XController = NewXController;
    OController = NewOController;
    XRLAgentSlot = NewXRLAgentSlot;
    ORLAgentSlot = NewORLAgentSlot;

    // Future RL training hook: connect the trainer here, using XRLAgentSlot and ORLAgentSlot
    // to choose which saved agent(s) are updated. For now training is only validated and acknowledged.
    return true;
}

ETicTacToeControllerType ATicTacToeGameMode::GetControllerForPlayer(ETileState Player) const
{
    return Player == ETileState::O ? OController : XController;
}

bool ATicTacToeGameMode::IsPlayerAI(ETileState Player) const
{
    return GetControllerForPlayer(Player) != ETicTacToeControllerType::Human;
}

FString ATicTacToeGameMode::GetPlayerLabel(ETileState Player) const
{
    const FString Symbol = Player == ETileState::O ? TEXT("O") : TEXT("X");
    const ETicTacToeControllerType ControllerType = GetControllerForPlayer(Player);

    if (ControllerType == ETicTacToeControllerType::Human)
    {
        return Symbol;
    }

    return FString::Printf(TEXT("%s %s"), *Symbol, *GetControllerLabel(ControllerType));
}

void ATicTacToeGameMode::ContinueAIMoveChain()
{
    int32 MoveGuard = Board.Num();

    while (!bGameOver && IsCurrentPlayerAI() && MoveGuard > 0)
    {
        if (!MakeAIMoveForCurrentPlayer())
        {
            return;
        }

        --MoveGuard;
    }
}

bool ATicTacToeGameMode::MakeAIMoveForCurrentPlayer()
{
    const ETicTacToeControllerType ControllerType = GetControllerForPlayer(CurrentPlayer);

    if (ControllerType == ETicTacToeControllerType::AlphaBetaAI)
    {
        return MakeAlphaBetaAIMove();
    }

    if (ControllerType == ETicTacToeControllerType::ReinforcementLearningAI)
    {
        return MakeReinforcementLearningAIMove();
    }

    if (ControllerType == ETicTacToeControllerType::RandomAI)
    {
        return MakeRandomAIMove();
    }

    return false;
}

bool ATicTacToeGameMode::MakeRandomAIMove()
{
    TArray<int32> EmptyTiles;
    FTicTacToeRules::GetAvailableMoves(Board, EmptyTiles);

    if (EmptyTiles.Num() == 0)
    {
        return false;
    }

    const int32 RandomTileIndex = FMath::RandRange(0, EmptyTiles.Num() - 1);
    return MakeMoveForCurrentPlayer(EmptyTiles[RandomTileIndex]);
}

bool ATicTacToeGameMode::MakeAlphaBetaAIMove()
{
    const ETileState AIPlayer = CurrentPlayer;
    const ETileState OpponentPlayer = AIPlayer == ETileState::X ? ETileState::O : ETileState::X;
    const int32 BestMove = FTicTacToeAlphaBetaAI::FindBestMove(Board, AIPlayer, OpponentPlayer);

    if (BestMove != INDEX_NONE)
    {
        return MakeMoveForCurrentPlayer(BestMove);
    }

    return false;
}

bool ATicTacToeGameMode::IsCurrentPlayerAI() const
{
    return IsPlayerAI(CurrentPlayer);
}

void ATicTacToeGameMode::UpdatePlayModeFromControllers()
{
    const bool bXIsHuman = XController == ETicTacToeControllerType::Human;
    const bool bOIsHuman = OController == ETicTacToeControllerType::Human;

    if (bXIsHuman && bOIsHuman)
    {
        PlayMode = ETicTacToePlayMode::PlayerVsPlayer;
        return;
    }

    if (!bXIsHuman && !bOIsHuman)
    {
        PlayMode = ETicTacToePlayMode::AIVsAI;
        return;
    }

    const ETicTacToeControllerType AIController = bXIsHuman ? OController : XController;

    if (AIController == ETicTacToeControllerType::AlphaBetaAI)
    {
        PlayMode = ETicTacToePlayMode::PlayerVsAlphaBetaAI;
    }
    else if (AIController == ETicTacToeControllerType::ReinforcementLearningAI)
    {
        PlayMode = ETicTacToePlayMode::PlayerVsReinforcementLearningAI;
    }
    else
    {
        PlayMode = ETicTacToePlayMode::PlayerVsRandomAI;
    }
}

ETicTacToeControllerType ATicTacToeGameMode::GetAIControllerType(ETicTacToeAIType AIType) const
{
    if (AIType == ETicTacToeAIType::AlphaBeta)
    {
        return ETicTacToeControllerType::AlphaBetaAI;
    }

    if (AIType == ETicTacToeAIType::ReinforcementLearning)
    {
        return ETicTacToeControllerType::ReinforcementLearningAI;
    }

    return ETicTacToeControllerType::RandomAI;
}

FString ATicTacToeGameMode::GetControllerLabel(ETicTacToeControllerType ControllerType) const
{
    if (ControllerType == ETicTacToeControllerType::AlphaBetaAI)
    {
        return TEXT("Alpha-Beta AI");
    }

    if (ControllerType == ETicTacToeControllerType::ReinforcementLearningAI)
    {
        return TEXT("Reinforcement Learning AI");
    }

    if (ControllerType == ETicTacToeControllerType::RandomAI)
    {
        return TEXT("Random AI");
    }

    return TEXT("Human");
}

bool ATicTacToeGameMode::MakeReinforcementLearningAIMove()
{
    // Future AlphaBeta/RL separation hook: replace this random move with inference from
    // the selected RL agent slot for CurrentPlayer.
    return MakeRandomAIMove();
}

void ATicTacToeGameMode::SwitchTurn()
{
    CurrentPlayer = CurrentPlayer == ETileState::X ? ETileState::O : ETileState::X;
}
