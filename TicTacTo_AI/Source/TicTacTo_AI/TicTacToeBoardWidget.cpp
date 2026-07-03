/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "TicTacToeBoardWidget.h"

#include "Components/Button.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Kismet/GameplayStatics.h"
#include "ATicTacToeGameMode.h"
#include "TicTacToeRLTrainingManager.h"

void UTicTacToeBoardWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (TileButton_0)
    {
        TileButton_0->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton0Clicked);
        TileButton_0->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton0Clicked);
    }

    if (TileButton_1)
    {
        TileButton_1->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton1Clicked);
        TileButton_1->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton1Clicked);
    }

    if (TileButton_2)
    {
        TileButton_2->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton2Clicked);
        TileButton_2->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton2Clicked);
    }

    if (TileButton_3)
    {
        TileButton_3->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton3Clicked);
        TileButton_3->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton3Clicked);
    }

    if (TileButton_4)
    {
        TileButton_4->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton4Clicked);
        TileButton_4->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton4Clicked);
    }

    if (TileButton_5)
    {
        TileButton_5->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton5Clicked);
        TileButton_5->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton5Clicked);
    }

    if (TileButton_6)
    {
        TileButton_6->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton6Clicked);
        TileButton_6->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton6Clicked);
    }

    if (TileButton_7)
    {
        TileButton_7->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton7Clicked);
        TileButton_7->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton7Clicked);
    }

    if (TileButton_8)
    {
        TileButton_8->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnTileButton8Clicked);
        TileButton_8->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnTileButton8Clicked);
    }

    if (RestartButton)
    {
        RestartButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnRestartClicked);
        RestartButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnRestartClicked);
    }

    if (BackButton)
    {
        BackButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnBackClicked);
        BackButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnBackClicked);
    }

    if (PlayerVsPlayerButton)
    {
        PlayerVsPlayerButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsPlayerClicked);
        PlayerVsPlayerButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsPlayerClicked);
    }

    if (PlayerVsAIButton)
    {
        PlayerVsAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsAIClicked);
        PlayerVsAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsAIClicked);
    }

    if (PlayerVsAlphaBetaAIButton)
    {
        PlayerVsAlphaBetaAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsAlphaBetaAIClicked);
        PlayerVsAlphaBetaAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsAlphaBetaAIClicked);
    }

    if (PlayerVsReinforcementLearningAIButton)
    {
        PlayerVsReinforcementLearningAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsReinforcementLearningAIClicked);
        PlayerVsReinforcementLearningAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsReinforcementLearningAIClicked);
    }

    if (AIVsAIButton)
    {
        AIVsAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnAIVsAIClicked);
        AIVsAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnAIVsAIClicked);
    }

    if (PlayerXButton)
    {
        PlayerXButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPlayerXClicked);
        PlayerXButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPlayerXClicked);
    }

    if (PlayerOButton)
    {
        PlayerOButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPlayerOClicked);
        PlayerOButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPlayerOClicked);
    }

    if (RandomAIButton)
    {
        RandomAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnRandomAIClicked);
        RandomAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnRandomAIClicked);
    }

    if (PlayerVsRandomAIButton)
    {
        PlayerVsRandomAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsRandomAIClicked);
        PlayerVsRandomAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPlayerVsRandomAIClicked);
    }

    if (AlphaBetaAIButton)
    {
        AlphaBetaAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnAlphaBetaAIClicked);
        AlphaBetaAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnAlphaBetaAIClicked);
    }

    if (ReinforcementLearningAIButton)
    {
        ReinforcementLearningAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnReinforcementLearningAIClicked);
        ReinforcementLearningAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnReinforcementLearningAIClicked);
    }

    if (PreviousAIButton)
    {
        PreviousAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPreviousAIClicked);
        PreviousAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPreviousAIClicked);
    }

    if (NextAIButton)
    {
        NextAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnNextAIClicked);
        NextAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnNextAIClicked);
    }

    if (PreviousXAIButton)
    {
        PreviousXAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPreviousXAIClicked);
        PreviousXAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPreviousXAIClicked);
    }

    if (NextXAIButton)
    {
        NextXAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnNextXAIClicked);
        NextXAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnNextXAIClicked);
    }

    if (PreviousOAIButton)
    {
        PreviousOAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnPreviousOAIClicked);
        PreviousOAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnPreviousOAIClicked);
    }

    if (NextOAIButton)
    {
        NextOAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnNextOAIClicked);
        NextOAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnNextOAIClicked);
    }

    if (ToggleSideButton)
    {
        ToggleSideButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnToggleSideClicked);
        ToggleSideButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnToggleSideClicked);
    }

    if (ConfirmAIButton)
    {
        ConfirmAIButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnConfirmAIClicked);
        ConfirmAIButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnConfirmAIClicked);
    }

    if (LeftControllerPreviousButton)
    {
        LeftControllerPreviousButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnLeftControllerPreviousClicked);
        LeftControllerPreviousButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnLeftControllerPreviousClicked);
    }

    if (LeftControllerNextButton)
    {
        LeftControllerNextButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnLeftControllerNextClicked);
        LeftControllerNextButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnLeftControllerNextClicked);
    }

    if (RightControllerPreviousButton)
    {
        RightControllerPreviousButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnRightControllerPreviousClicked);
        RightControllerPreviousButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnRightControllerPreviousClicked);
    }

    if (RightControllerNextButton)
    {
        RightControllerNextButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnRightControllerNextClicked);
        RightControllerNextButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnRightControllerNextClicked);
    }

    if (LeftRLAgentPreviousButton)
    {
        LeftRLAgentPreviousButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnLeftRLAgentPreviousClicked);
        LeftRLAgentPreviousButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnLeftRLAgentPreviousClicked);
    }

    if (LeftRLAgentNextButton)
    {
        LeftRLAgentNextButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnLeftRLAgentNextClicked);
        LeftRLAgentNextButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnLeftRLAgentNextClicked);
    }

    if (RightRLAgentPreviousButton)
    {
        RightRLAgentPreviousButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnRightRLAgentPreviousClicked);
        RightRLAgentPreviousButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnRightRLAgentPreviousClicked);
    }

    if (RightRLAgentNextButton)
    {
        RightRLAgentNextButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnRightRLAgentNextClicked);
        RightRLAgentNextButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnRightRLAgentNextClicked);
    }

    if (MenuActionPreviousButton)
    {
        MenuActionPreviousButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnMenuActionPreviousClicked);
        MenuActionPreviousButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnMenuActionPreviousClicked);
    }

    if (MenuActionNextButton)
    {
        MenuActionNextButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnMenuActionNextClicked);
        MenuActionNextButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnMenuActionNextClicked);
    }

    if (MainActionButton)
    {
        MainActionButton->OnClicked.RemoveDynamic(this, &UTicTacToeBoardWidget::OnMainActionClicked);
        MainActionButton->OnClicked.AddDynamic(this, &UTicTacToeBoardWidget::OnMainActionClicked);
    }

    InitializeTrainingSettingsUI();
    ShowModeSelect();
}

UButton* UTicTacToeBoardWidget::GetRandomAIButton() const
{
    if (RandomAIButton)
    {
        return RandomAIButton;
    }

    if (PlayerVsRandomAIButton)
    {
        return PlayerVsRandomAIButton;
    }

    return nullptr;
}

void UTicTacToeBoardWidget::OnTileButton0Clicked()
{
    HandleTileClicked(0);
}

void UTicTacToeBoardWidget::OnTileButton1Clicked()
{
    HandleTileClicked(1);
}

void UTicTacToeBoardWidget::OnTileButton2Clicked()
{
    HandleTileClicked(2);
}

void UTicTacToeBoardWidget::OnTileButton3Clicked()
{
    HandleTileClicked(3);
}

void UTicTacToeBoardWidget::OnTileButton4Clicked()
{
    HandleTileClicked(4);
}

void UTicTacToeBoardWidget::OnTileButton5Clicked()
{
    HandleTileClicked(5);
}

void UTicTacToeBoardWidget::OnTileButton6Clicked()
{
    HandleTileClicked(6);
}

void UTicTacToeBoardWidget::OnTileButton7Clicked()
{
    HandleTileClicked(7);
}

void UTicTacToeBoardWidget::OnTileButton8Clicked()
{
    HandleTileClicked(8);
}

void UTicTacToeBoardWidget::OnRestartClicked()
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    TicTacToeGameMode->ResetGame();
    ShowBoard();
    UpdateBoardUI();
}

void UTicTacToeBoardWidget::OnBackClicked()
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        ShowModeSelect();
        return;
    }

    const bool bHasSeparateAISelectScene = AISelectPanel
        || SideSelectPanel
        || GetRandomAIButton()
        || AlphaBetaAIButton
        || ReinforcementLearningAIButton
        || ConfirmAIButton
        || PreviousAIButton
        || NextAIButton
        || PreviousXAIButton
        || NextXAIButton
        || PreviousOAIButton
        || NextOAIButton
        || ToggleSideButton;
    if (!bHasSeparateAISelectScene)
    {
        ShowModeSelect();
        return;
    }

    const auto ControllerToAIType = [](ETicTacToeControllerType ControllerType)
    {
        if (ControllerType == ETicTacToeControllerType::RandomAI)
        {
            return ETicTacToeAIType::Random;
        }

        if (ControllerType == ETicTacToeControllerType::ReinforcementLearningAI)
        {
            return ETicTacToeAIType::ReinforcementLearning;
        }

        return ETicTacToeAIType::AlphaBeta;
    };

    const ETicTacToePlayMode CurrentPlayMode = TicTacToeGameMode->GetPlayMode();
    if (CurrentPlayMode == ETicTacToePlayMode::AIVsAI)
    {
        PendingMatchMode = ETicTacToeMatchMode::AIVsAI;
        PendingXAIType = ControllerToAIType(TicTacToeGameMode->GetControllerForPlayer(ETileState::X));
        PendingOAIType = ControllerToAIType(TicTacToeGameMode->GetControllerForPlayer(ETileState::O));
        ShowAISelect();
        return;
    }

    if (CurrentPlayMode == ETicTacToePlayMode::PlayerVsRandomAI
        || CurrentPlayMode == ETicTacToePlayMode::PlayerVsAlphaBetaAI
        || CurrentPlayMode == ETicTacToePlayMode::PlayerVsReinforcementLearningAI)
    {
        PendingMatchMode = ETicTacToeMatchMode::PlayerVsAI;
        if (CurrentPlayMode == ETicTacToePlayMode::PlayerVsRandomAI)
        {
            PendingAIType = ETicTacToeAIType::Random;
        }
        else if (CurrentPlayMode == ETicTacToePlayMode::PlayerVsReinforcementLearningAI)
        {
            PendingAIType = ETicTacToeAIType::ReinforcementLearning;
        }
        else
        {
            PendingAIType = ETicTacToeAIType::AlphaBeta;
        }

        PendingHumanSide = TicTacToeGameMode->IsPlayerAI(ETileState::X) ? ETileState::O : ETileState::X;
        ShowAISelect();
        return;
    }

    ShowModeSelect();
}

void UTicTacToeBoardWidget::OnPlayerVsPlayerClicked()
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    TicTacToeGameMode->SetPlayerVsPlayer();
    ShowBoard();
}

void UTicTacToeBoardWidget::OnPlayerVsAIClicked()
{
    PendingMatchMode = ETicTacToeMatchMode::PlayerVsAI;
    PendingAIType = ETicTacToeAIType::AlphaBeta;
    PendingHumanSide = ETileState::X;
    ShowAISelect();
}

void UTicTacToeBoardWidget::OnPlayerVsAlphaBetaAIClicked()
{
    if (PendingMatchMode == ETicTacToeMatchMode::PlayerVsAI || PendingMatchMode == ETicTacToeMatchMode::AIVsAI)
    {
        HandleAITypeSelected(ETicTacToeAIType::AlphaBeta);
        return;
    }

    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    TicTacToeGameMode->SetPlayerVsAI(ETileState::X, ETicTacToeAIType::AlphaBeta);
    ShowBoard();
}

void UTicTacToeBoardWidget::OnPlayerVsReinforcementLearningAIClicked()
{
    if (PendingMatchMode == ETicTacToeMatchMode::PlayerVsAI || PendingMatchMode == ETicTacToeMatchMode::AIVsAI)
    {
        HandleAITypeSelected(ETicTacToeAIType::ReinforcementLearning);
        return;
    }

    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    TicTacToeGameMode->SetPlayerVsAI(ETileState::X, ETicTacToeAIType::ReinforcementLearning);
    ShowBoard();
}

void UTicTacToeBoardWidget::OnAIVsAIClicked()
{
    if (!AISelectPanel && !GetRandomAIButton() && !AlphaBetaAIButton && !ReinforcementLearningAIButton)
    {
        ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
        if (TicTacToeGameMode)
        {
            TicTacToeGameMode->SetAIVsAI(ETicTacToeAIType::AlphaBeta, ETicTacToeAIType::AlphaBeta);
            ShowBoard();
        }
        return;
    }

    PendingMatchMode = ETicTacToeMatchMode::AIVsAI;
    PendingXAIType = ETicTacToeAIType::AlphaBeta;
    PendingOAIType = ETicTacToeAIType::AlphaBeta;
    ShowAISelect();
}

void UTicTacToeBoardWidget::OnPlayerXClicked()
{
    PendingHumanSide = ETileState::X;
    RefreshDeploymentSelectionUI();
}

void UTicTacToeBoardWidget::OnPlayerOClicked()
{
    PendingHumanSide = ETileState::O;
    RefreshDeploymentSelectionUI();
}

void UTicTacToeBoardWidget::OnRandomAIClicked()
{
    HandleAITypeSelected(ETicTacToeAIType::Random);
}

void UTicTacToeBoardWidget::OnPlayerVsRandomAIClicked()
{
    HandleAITypeSelected(ETicTacToeAIType::Random);
}

void UTicTacToeBoardWidget::OnAlphaBetaAIClicked()
{
    HandleAITypeSelected(ETicTacToeAIType::AlphaBeta);
}

void UTicTacToeBoardWidget::OnReinforcementLearningAIClicked()
{
    HandleAITypeSelected(ETicTacToeAIType::ReinforcementLearning);
}

void UTicTacToeBoardWidget::OnPreviousAIClicked()
{
    ChangePendingAIType(-1);
}

void UTicTacToeBoardWidget::OnNextAIClicked()
{
    ChangePendingAIType(1);
}

void UTicTacToeBoardWidget::OnPreviousXAIClicked()
{
    ChangePendingXAIType(-1);
}

void UTicTacToeBoardWidget::OnNextXAIClicked()
{
    ChangePendingXAIType(1);
}

void UTicTacToeBoardWidget::OnPreviousOAIClicked()
{
    ChangePendingOAIType(-1);
}

void UTicTacToeBoardWidget::OnNextOAIClicked()
{
    ChangePendingOAIType(1);
}

void UTicTacToeBoardWidget::OnToggleSideClicked()
{
    PendingHumanSide = PendingHumanSide == ETileState::X ? ETileState::O : ETileState::X;
    RefreshDeploymentSelectionUI();
}

void UTicTacToeBoardWidget::OnConfirmAIClicked()
{
    DeployPendingAISelection();
}

void UTicTacToeBoardWidget::OnLeftControllerPreviousClicked()
{
    CycleLeftControllerType(-1);
}

void UTicTacToeBoardWidget::OnLeftControllerNextClicked()
{
    CycleLeftControllerType(1);
}

void UTicTacToeBoardWidget::OnRightControllerPreviousClicked()
{
    CycleRightControllerType(-1);
}

void UTicTacToeBoardWidget::OnRightControllerNextClicked()
{
    CycleRightControllerType(1);
}

void UTicTacToeBoardWidget::OnLeftRLAgentPreviousClicked()
{
    CycleLeftRLAgentSlot(-1);
}

void UTicTacToeBoardWidget::OnLeftRLAgentNextClicked()
{
    CycleLeftRLAgentSlot(1);
}

void UTicTacToeBoardWidget::OnRightRLAgentPreviousClicked()
{
    CycleRightRLAgentSlot(-1);
}

void UTicTacToeBoardWidget::OnRightRLAgentNextClicked()
{
    CycleRightRLAgentSlot(1);
}

void UTicTacToeBoardWidget::OnMenuActionPreviousClicked()
{
    CycleMenuAction(-1);
}

void UTicTacToeBoardWidget::OnMenuActionNextClicked()
{
    CycleMenuAction(1);
}

void UTicTacToeBoardWidget::OnMainActionClicked()
{
    if (CurrentMenuAction == ETicTacToeMenuAction::Train)
    {
        if (!ValidateTrainingSetup())
        {
            if (MenuWarningText)
            {
                MenuWarningText->SetText(FText::FromString(TEXT("Training requires at least one RL agent.")));
                MenuWarningText->SetVisibility(ESlateVisibility::Visible);
            }
            return;
        }

        StartRLTrainingPlaceholder();
        return;
    }

    StartMatch();
}

void UTicTacToeBoardWidget::DeployPendingAISelection()
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    if (PendingMatchMode == ETicTacToeMatchMode::AIVsAI)
    {
        TicTacToeGameMode->SetAIVsAI(PendingXAIType, PendingOAIType);
        ShowBoard();
        return;
    }

    TicTacToeGameMode->SetPlayerVsAI(PendingHumanSide, PendingAIType);
    ShowBoard();
}

void UTicTacToeBoardWidget::HandleAITypeSelected(ETicTacToeAIType AIType)
{
    if (PendingMatchMode == ETicTacToeMatchMode::AIVsAI)
    {
        PendingXAIType = AIType;
        PendingOAIType = AIType;
        if (ShouldDeployAISelectionImmediately())
        {
            DeployPendingAISelection();
            return;
        }

        RefreshDeploymentSelectionUI();
        return;
    }

    PendingAIType = AIType;
    if (ShouldDeployAISelectionImmediately())
    {
        DeployPendingAISelection();
        return;
    }

    RefreshDeploymentSelectionUI();
}

bool UTicTacToeBoardWidget::ShouldDeployAISelectionImmediately() const
{
    return !ConfirmAIButton
        && !PreviousAIButton
        && !NextAIButton
        && !PreviousXAIButton
        && !NextXAIButton
        && !PreviousOAIButton
        && !NextOAIButton
        && !ToggleSideButton;
}

void UTicTacToeBoardWidget::ChangePendingAIType(int32 Direction)
{
    PendingAIType = GetNextAIType(PendingAIType, Direction);
    RefreshDeploymentSelectionUI();
}

void UTicTacToeBoardWidget::ChangePendingXAIType(int32 Direction)
{
    PendingXAIType = GetNextAIType(PendingXAIType, Direction);
    RefreshDeploymentSelectionUI();
}

void UTicTacToeBoardWidget::ChangePendingOAIType(int32 Direction)
{
    PendingOAIType = GetNextAIType(PendingOAIType, Direction);
    RefreshDeploymentSelectionUI();
}

ETicTacToeAIType UTicTacToeBoardWidget::GetNextAIType(ETicTacToeAIType AIType, int32 Direction) const
{
    constexpr int32 AITypeCount = 3;
    int32 AITypeIndex = 0;

    if (AIType == ETicTacToeAIType::AlphaBeta)
    {
        AITypeIndex = 1;
    }
    else if (AIType == ETicTacToeAIType::ReinforcementLearning)
    {
        AITypeIndex = 2;
    }

    AITypeIndex = (AITypeIndex + Direction) % AITypeCount;
    if (AITypeIndex < 0)
    {
        AITypeIndex += AITypeCount;
    }

    if (AITypeIndex == 1)
    {
        return ETicTacToeAIType::AlphaBeta;
    }

    if (AITypeIndex == 2)
    {
        return ETicTacToeAIType::ReinforcementLearning;
    }

    return ETicTacToeAIType::Random;
}

FString UTicTacToeBoardWidget::GetAITypeLabel(ETicTacToeAIType AIType) const
{
    if (AIType == ETicTacToeAIType::AlphaBeta)
    {
        return TEXT("Alpha-Beta");
    }

    if (AIType == ETicTacToeAIType::ReinforcementLearning)
    {
        return TEXT("Reinforcement Learning");
    }

    return TEXT("Random");
}

void UTicTacToeBoardWidget::RefreshDeploymentSelectionUI()
{
    if (SelectedAIText)
    {
        SelectedAIText->SetText(FText::FromString(GetAITypeLabel(PendingAIType)));
    }

    if (SelectedXAIText)
    {
        SelectedXAIText->SetText(FText::FromString(GetAITypeLabel(PendingXAIType)));
    }

    if (SelectedOAIText)
    {
        SelectedOAIText->SetText(FText::FromString(GetAITypeLabel(PendingOAIType)));
    }

    if (SelectedSideText)
    {
        const FString SideLabel = PendingHumanSide == ETileState::X ? TEXT("Player 1 (X)") : TEXT("Player 2 (O)");
        SelectedSideText->SetText(FText::FromString(SideLabel));
    }

    if (StatusText)
    {
        const FString Prompt = PendingMatchMode == ETicTacToeMatchMode::AIVsAI
            ? TEXT("Deploy AI for both sides")
            : TEXT("Deploy AI");
        StatusText->SetText(FText::FromString(Prompt));
    }
}

void UTicTacToeBoardWidget::CycleLeftControllerType(int32 Direction)
{
    LeftControllerType = GetNextControllerType(LeftControllerType, Direction);
    UpdateSelectionUI();
}

void UTicTacToeBoardWidget::CycleRightControllerType(int32 Direction)
{
    RightControllerType = GetNextControllerType(RightControllerType, Direction);
    UpdateSelectionUI();
}

void UTicTacToeBoardWidget::CycleMenuAction(int32 Direction)
{
    CurrentMenuAction = CurrentMenuAction == ETicTacToeMenuAction::Play
        ? ETicTacToeMenuAction::Train
        : ETicTacToeMenuAction::Play;
    UpdateSelectionUI();
}

void UTicTacToeBoardWidget::CycleLeftRLAgentSlot(int32 Direction)
{
    LeftRLAgentSlot = GetNextRLAgentSlot(LeftRLAgentSlot, Direction);
    UpdateSelectionUI();
}

void UTicTacToeBoardWidget::CycleRightRLAgentSlot(int32 Direction)
{
    RightRLAgentSlot = GetNextRLAgentSlot(RightRLAgentSlot, Direction);
    UpdateSelectionUI();
}

ETicTacToeControllerType UTicTacToeBoardWidget::GetNextControllerType(ETicTacToeControllerType ControllerType, int32 Direction) const
{
    constexpr int32 ControllerTypeCount = 4;
    int32 ControllerIndex = 0;

    if (ControllerType == ETicTacToeControllerType::RandomAI)
    {
        ControllerIndex = 1;
    }
    else if (ControllerType == ETicTacToeControllerType::AlphaBetaAI)
    {
        ControllerIndex = 2;
    }
    else if (ControllerType == ETicTacToeControllerType::ReinforcementLearningAI)
    {
        ControllerIndex = 3;
    }

    ControllerIndex = (ControllerIndex + Direction) % ControllerTypeCount;
    if (ControllerIndex < 0)
    {
        ControllerIndex += ControllerTypeCount;
    }

    if (ControllerIndex == 1)
    {
        return ETicTacToeControllerType::RandomAI;
    }

    if (ControllerIndex == 2)
    {
        return ETicTacToeControllerType::AlphaBetaAI;
    }

    if (ControllerIndex == 3)
    {
        return ETicTacToeControllerType::ReinforcementLearningAI;
    }

    return ETicTacToeControllerType::Human;
}

ETicTacToeRLAgentSlot UTicTacToeBoardWidget::GetNextRLAgentSlot(ETicTacToeRLAgentSlot AgentSlot, int32 Direction) const
{
    constexpr int32 AgentSlotCount = 3;
    int32 AgentSlotIndex = 0;

    if (AgentSlot == ETicTacToeRLAgentSlot::Slot2)
    {
        AgentSlotIndex = 1;
    }
    else if (AgentSlot == ETicTacToeRLAgentSlot::Slot3)
    {
        AgentSlotIndex = 2;
    }

    AgentSlotIndex = (AgentSlotIndex + Direction) % AgentSlotCount;
    if (AgentSlotIndex < 0)
    {
        AgentSlotIndex += AgentSlotCount;
    }

    if (AgentSlotIndex == 1)
    {
        return ETicTacToeRLAgentSlot::Slot2;
    }

    if (AgentSlotIndex == 2)
    {
        return ETicTacToeRLAgentSlot::Slot3;
    }

    return ETicTacToeRLAgentSlot::Slot1;
}

FString UTicTacToeBoardWidget::GetControllerTypeLabel(ETicTacToeControllerType ControllerType) const
{
    if (ControllerType == ETicTacToeControllerType::RandomAI)
    {
        return TEXT("AI Random");
    }

    if (ControllerType == ETicTacToeControllerType::AlphaBetaAI)
    {
        // Future AlphaBeta hook: this label maps to the existing alpha-beta move search.
        return TEXT("AI AlphaBeta");
    }

    if (ControllerType == ETicTacToeControllerType::ReinforcementLearningAI)
    {
        // Future RL hook: this side will load the selected saved RL agent slot.
        return TEXT("AI RL");
    }

    return TEXT("Human Player");
}

FString UTicTacToeBoardWidget::GetRLAgentSlotLabel(ETicTacToeRLAgentSlot AgentSlot) const
{
    if (AgentSlot == ETicTacToeRLAgentSlot::Slot2)
    {
        return TEXT("RL Agent Slot 2");
    }

    if (AgentSlot == ETicTacToeRLAgentSlot::Slot3)
    {
        return TEXT("RL Agent Slot 3");
    }

    return TEXT("RL Agent Slot 1");
}

FString UTicTacToeBoardWidget::GetRLAgentSaveSlotName(ETicTacToeRLAgentSlot AgentSlot) const
{
    if (AgentSlot == ETicTacToeRLAgentSlot::Slot2)
    {
        return TEXT("TicTacToeRL_Slot2");
    }

    if (AgentSlot == ETicTacToeRLAgentSlot::Slot3)
    {
        return TEXT("TicTacToeRL_Slot3");
    }

    return TEXT("TicTacToeRL_Slot1");
}

FString UTicTacToeBoardWidget::GetMenuActionLabel(ETicTacToeMenuAction MenuAction) const
{
    return MenuAction == ETicTacToeMenuAction::Train ? TEXT("Train") : TEXT("Play");
}

void UTicTacToeBoardWidget::UpdateSelectionUI()
{
    if (LeftControllerText)
    {
        LeftControllerText->SetText(FText::FromString(GetControllerTypeLabel(LeftControllerType)));
    }

    if (RightControllerText)
    {
        RightControllerText->SetText(FText::FromString(GetControllerTypeLabel(RightControllerType)));
    }

    const bool bLeftUsesRL = LeftControllerType == ETicTacToeControllerType::ReinforcementLearningAI;
    const bool bRightUsesRL = RightControllerType == ETicTacToeControllerType::ReinforcementLearningAI;
    SetPanelVisibility(LeftRLAgentPanel, bLeftUsesRL);
    SetPanelVisibility(RightRLAgentPanel, bRightUsesRL);

    if (LeftRLAgentText)
    {
        LeftRLAgentText->SetText(FText::FromString(GetRLAgentSlotLabel(LeftRLAgentSlot)));
    }

    if (RightRLAgentText)
    {
        RightRLAgentText->SetText(FText::FromString(GetRLAgentSlotLabel(RightRLAgentSlot)));
    }

    const FString ActionLabel = GetMenuActionLabel(CurrentMenuAction);
    if (MenuActionText)
    {
        MenuActionText->SetText(FText::FromString(ActionLabel));
    }

    if (MainActionButtonText)
    {
        MainActionButtonText->SetText(FText::FromString(ActionLabel));
    }

    if (MenuWarningText)
    {
        MenuWarningText->SetText(FText::GetEmpty());
        MenuWarningText->SetVisibility(ESlateVisibility::Collapsed);
    }

    if (StatusText)
    {
        StatusText->SetText(FText::FromString(TEXT("Configure both sides")));
    }

    RefreshTrainingSettingsUI();
}

bool UTicTacToeBoardWidget::ValidateTrainingSetup() const
{
    return LeftControllerType == ETicTacToeControllerType::ReinforcementLearningAI
        || RightControllerType == ETicTacToeControllerType::ReinforcementLearningAI;
}

void UTicTacToeBoardWidget::InitializeTrainingSettingsUI()
{
    if (TrainingEpisodeSpinBox)
    {
        TrainingEpisodeSpinBox->SetMinValue(1.0f);
        TrainingEpisodeSpinBox->SetMinSliderValue(1.0f);
        TrainingEpisodeSpinBox->SetMaxSliderValue(100000.0f);
        TrainingEpisodeSpinBox->SetValue(static_cast<float>(PendingTrainingSettings.EpisodeCount));
    }

    USpinBox* RateSpinBoxes[] =
    {
        LearningRateSpinBox,
        DiscountFactorSpinBox,
        ExplorationRateSpinBox
    };

    for (USpinBox* SpinBox : RateSpinBoxes)
    {
        if (SpinBox)
        {
            SpinBox->SetMinValue(0.0f);
            SpinBox->SetMaxValue(1.0f);
            SpinBox->SetMinSliderValue(0.0f);
            SpinBox->SetMaxSliderValue(1.0f);
        }
    }

    if (LearningRateSpinBox)
    {
        LearningRateSpinBox->SetValue(PendingTrainingSettings.LearningRate);
    }

    if (DiscountFactorSpinBox)
    {
        DiscountFactorSpinBox->SetValue(PendingTrainingSettings.DiscountFactor);
    }

    if (ExplorationRateSpinBox)
    {
        ExplorationRateSpinBox->SetValue(PendingTrainingSettings.ExplorationRate);
    }
}

void UTicTacToeBoardWidget::RefreshTrainingSettingsUI()
{
    SetTrainingSettingsControlsVisibility(CurrentMenuAction == ETicTacToeMenuAction::Train);
}

FTicTacToeRLTrainingSettings UTicTacToeBoardWidget::GetTrainingSettingsFromUI() const
{
    FTicTacToeRLTrainingSettings Settings = PendingTrainingSettings;

    if (TrainingEpisodeSpinBox)
    {
        Settings.EpisodeCount = FMath::Max(1, FMath::RoundToInt(TrainingEpisodeSpinBox->GetValue()));
    }

    if (LearningRateSpinBox)
    {
        Settings.LearningRate = FMath::Clamp(LearningRateSpinBox->GetValue(), 0.0f, 1.0f);
    }

    if (DiscountFactorSpinBox)
    {
        Settings.DiscountFactor = FMath::Clamp(DiscountFactorSpinBox->GetValue(), 0.0f, 1.0f);
    }

    if (ExplorationRateSpinBox)
    {
        Settings.ExplorationRate = FMath::Clamp(ExplorationRateSpinBox->GetValue(), 0.0f, 1.0f);
    }

    return Settings;
}

void UTicTacToeBoardWidget::SetTrainingSettingsControlsVisibility(bool bVisible) const
{
    UWidget* TrainingSettingsControls[] =
    {
        TrainingSettingsPanel,
        TrainingEpisodeSpinBox,
        LearningRateSpinBox,
        DiscountFactorSpinBox,
        ExplorationRateSpinBox
    };

    for (UWidget* Widget : TrainingSettingsControls)
    {
        SetPanelVisibility(Widget, bVisible);
    }
}

void UTicTacToeBoardWidget::StartMatch()
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    TicTacToeGameMode->StartConfiguredMatch(LeftControllerType, RightControllerType, LeftRLAgentSlot, RightRLAgentSlot);
    ShowBoard();
}

void UTicTacToeBoardWidget::StartRLTrainingPlaceholder()
{
    UTicTacToeRLTrainingManager* TrainingManager = NewObject<UTicTacToeRLTrainingManager>(this);
    if (!TrainingManager)
    {
        return;
    }

    PendingTrainingSettings = GetTrainingSettingsFromUI();
    const ETicTacToeRLAgentSlot TrainingSlot = LeftControllerType == ETicTacToeControllerType::ReinforcementLearningAI
        ? LeftRLAgentSlot
        : RightRLAgentSlot;
    const FString SaveSlotName = GetRLAgentSaveSlotName(TrainingSlot);

    TrainingManager->SetTrainingSettings(PendingTrainingSettings);
    const FTicTacToeRLTrainingStats TrainingStats = TrainingManager->TrainAgentVsRandom(PendingTrainingSettings.EpisodeCount, SaveSlotName);

    if (MenuWarningText)
    {
        MenuWarningText->SetText(FText::FromString(FString::Printf(
            TEXT("RL training complete: %d episodes, wins %d, losses %d, draws %d."),
            TrainingStats.TotalEpisodes,
            TrainingStats.RLWins,
            TrainingStats.RLLosses,
            TrainingStats.Draws)));
        MenuWarningText->SetVisibility(ESlateVisibility::Visible);
    }
}

void UTicTacToeBoardWidget::HandleTileClicked(int32 Index)
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    TicTacToeGameMode->MakeMove(Index);
    UpdateBoardUI();
}

void UTicTacToeBoardWidget::ShowModeSelect()
{
    const bool bUseSelectionMenu = SelectionMenuPanel != nullptr;

    SetPanelVisibility(SelectionMenuPanel, true);
    SetPanelVisibility(ModeSelectPanel, !bUseSelectionMenu);
    SetPanelVisibility(SideSelectPanel, false);
    SetPanelVisibility(AISelectPanel, false);
    SetPanelVisibility(BoardPanel, false);
    SetBoardControlsVisibility(false);
    SetModeControlsVisibility(!bUseSelectionMenu);
    SetSideControlsVisibility(false);
    SetAIControlsVisibility(false);
    SetDeploymentSwitchControlsVisibility(false);

    if (bUseSelectionMenu)
    {
        UpdateSelectionUI();
    }
    else if (StatusText)
    {
        StatusText->SetText(FText::FromString(TEXT("Choose a mode")));
    }
}

void UTicTacToeBoardWidget::ShowSideSelect()
{
    SetPanelVisibility(SelectionMenuPanel, false);
    SetPanelVisibility(ModeSelectPanel, false);
    SetPanelVisibility(SideSelectPanel, true);
    SetPanelVisibility(AISelectPanel, false);
    SetPanelVisibility(BoardPanel, false);
    SetBoardControlsVisibility(false);
    SetModeControlsVisibility(false);
    SetSideControlsVisibility(true);
    SetAIControlsVisibility(false);
    SetDeploymentSwitchControlsVisibility(false);

    if (StatusText)
    {
        StatusText->SetText(FText::FromString(TEXT("Choose your side")));
    }
}

void UTicTacToeBoardWidget::ShowAISelect()
{
    SetPanelVisibility(SelectionMenuPanel, false);
    SetPanelVisibility(ModeSelectPanel, false);
    SetPanelVisibility(SideSelectPanel, false);
    SetPanelVisibility(AISelectPanel, true);
    SetPanelVisibility(BoardPanel, false);
    SetBoardControlsVisibility(false);
    SetModeControlsVisibility(false);
    SetSideControlsVisibility(PendingMatchMode == ETicTacToeMatchMode::PlayerVsAI);
    SetAIControlsVisibility(true);
    SetDeploymentSwitchControlsVisibility(true);
    RefreshDeploymentSelectionUI();
}

void UTicTacToeBoardWidget::ShowBoard()
{
    SetPanelVisibility(SelectionMenuPanel, false);
    SetPanelVisibility(ModeSelectPanel, false);
    SetPanelVisibility(SideSelectPanel, false);
    SetPanelVisibility(AISelectPanel, false);
    SetPanelVisibility(BoardPanel, true);
    SetBoardControlsVisibility(true);
    SetModeControlsVisibility(false);
    SetSideControlsVisibility(false);
    SetAIControlsVisibility(false);
    SetDeploymentSwitchControlsVisibility(false);
    UpdateBoardUI();
}

void UTicTacToeBoardWidget::SetPanelVisibility(UWidget* Panel, bool bVisible) const
{
    if (Panel)
    {
        Panel->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}

void UTicTacToeBoardWidget::SetBoardControlsVisibility(bool bVisible) const
{
    // Board page: controls visible while a match is being played.
    UWidget* BoardControls[] =
    {
        TileButton_0,
        TileButton_1,
        TileButton_2,
        TileButton_3,
        TileButton_4,
        TileButton_5,
        TileButton_6,
        TileButton_7,
        TileButton_8,
        TileText_0,
        TileText_1,
        TileText_2,
        TileText_3,
        TileText_4,
        TileText_5,
        TileText_6,
        TileText_7,
        TileText_8,
        RestartButton,
        BackButton,
        ModeText
    };

    for (UWidget* Widget : BoardControls)
    {
        SetPanelVisibility(Widget, bVisible);
    }
}

void UTicTacToeBoardWidget::SetModeControlsVisibility(bool bVisible) const
{
    // Mode select page: legacy/simple menu buttons.
    UWidget* ModeControls[] =
    {
        PlayerVsPlayerButton,
        PlayerVsAIButton,
        AIVsAIButton
    };

    for (UWidget* Widget : ModeControls)
    {
        SetPanelVisibility(Widget, bVisible);
    }
}

void UTicTacToeBoardWidget::SetSideControlsVisibility(bool bVisible) const
{
    // Side select page: human side choice for Player vs AI.
    UWidget* SideControls[] =
    {
        PlayerXButton,
        PlayerOButton
    };

    for (UWidget* Widget : SideControls)
    {
        SetPanelVisibility(Widget, bVisible);
    }
}

void UTicTacToeBoardWidget::SetAIControlsVisibility(bool bVisible) const
{
    // AI select page: AI type choices, including older and newer button names.
    UWidget* AIControls[] =
    {
        GetRandomAIButton(),
        PlayerVsRandomAIButton,
        AlphaBetaAIButton,
        ReinforcementLearningAIButton,
        PlayerVsAlphaBetaAIButton,
        PlayerVsReinforcementLearningAIButton
    };

    for (UWidget* Widget : AIControls)
    {
        SetPanelVisibility(Widget, bVisible);
    }
}

void UTicTacToeBoardWidget::SetDeploymentSwitchControlsVisibility(bool bVisible) const
{
    const bool bShowPlayerVsAIControls = bVisible && PendingMatchMode == ETicTacToeMatchMode::PlayerVsAI;
    const bool bShowAIVsAIControls = bVisible && PendingMatchMode == ETicTacToeMatchMode::AIVsAI;

    // AI select page: carousel controls for Player vs AI.
    UWidget* PlayerVsAIControls[] =
    {
        PreviousAIButton,
        NextAIButton,
        ToggleSideButton,
        SelectedAIText,
        SelectedSideText
    };

    // AI select page: carousel controls for AI vs AI.
    UWidget* AIVsAIControls[] =
    {
        PreviousXAIButton,
        NextXAIButton,
        PreviousOAIButton,
        NextOAIButton,
        SelectedXAIText,
        SelectedOAIText
    };

    for (UWidget* Widget : PlayerVsAIControls)
    {
        SetPanelVisibility(Widget, bShowPlayerVsAIControls);
    }

    for (UWidget* Widget : AIVsAIControls)
    {
        SetPanelVisibility(Widget, bShowAIVsAIControls);
    }

    SetPanelVisibility(ConfirmAIButton, bVisible);
}

void UTicTacToeBoardWidget::UpdateBoardUI()
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    UTextBlock* TileTexts[] =
    {
        TileText_0,
        TileText_1,
        TileText_2,
        TileText_3,
        TileText_4,
        TileText_5,
        TileText_6,
        TileText_7,
        TileText_8
    };

    for (int32 Index = 0; Index < UE_ARRAY_COUNT(TileTexts); ++Index)
    {
        if (TileTexts[Index])
        {
            TileTexts[Index]->SetText(FText::FromString(TicTacToeGameMode->GetTileText(Index)));
        }
    }

    if (StatusText)
    {
        StatusText->SetText(FText::FromString(TicTacToeGameMode->GetStatusText()));
    }

    if (ModeText)
    {
        FString ModeLabel = TEXT("Player vs Player");

        if (TicTacToeGameMode->GetPlayMode() == ETicTacToePlayMode::PlayerVsRandomAI)
        {
            ModeLabel = FString::Printf(TEXT("%s vs %s"), *TicTacToeGameMode->GetPlayerLabel(ETileState::X), *TicTacToeGameMode->GetPlayerLabel(ETileState::O));
        }
        else if (TicTacToeGameMode->GetPlayMode() == ETicTacToePlayMode::PlayerVsAlphaBetaAI)
        {
            ModeLabel = FString::Printf(TEXT("%s vs %s"), *TicTacToeGameMode->GetPlayerLabel(ETileState::X), *TicTacToeGameMode->GetPlayerLabel(ETileState::O));
        }
        else if (TicTacToeGameMode->GetPlayMode() == ETicTacToePlayMode::PlayerVsReinforcementLearningAI)
        {
            ModeLabel = FString::Printf(TEXT("%s vs %s"), *TicTacToeGameMode->GetPlayerLabel(ETileState::X), *TicTacToeGameMode->GetPlayerLabel(ETileState::O));
        }
        else if (TicTacToeGameMode->GetPlayMode() == ETicTacToePlayMode::AIVsAI)
        {
            ModeLabel = FString::Printf(TEXT("%s vs %s"), *TicTacToeGameMode->GetPlayerLabel(ETileState::X), *TicTacToeGameMode->GetPlayerLabel(ETileState::O));
        }

        ModeText->SetText(FText::FromString(ModeLabel));
    }
}
