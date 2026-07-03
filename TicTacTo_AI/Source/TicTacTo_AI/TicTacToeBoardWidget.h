/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TicTacToeTypes.h"
#include "TicTacToeBoardWidget.generated.h"

class UButton;
class USpinBox;
class UTextBlock;
class UWidget;

UCLASS()
class TICTACTO_AI_API UTicTacToeBoardWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* StatusText;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_0;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_1;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_2;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_3;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_4;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_5;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_6;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_7;

    UPROPERTY(meta = (BindWidget))
    UButton* TileButton_8;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_0;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_1;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_2;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_3;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_4;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_5;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_6;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_7;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TileText_8;

    UPROPERTY(meta = (BindWidget))
    UButton* RestartButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* ModeText;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PlayerVsPlayerButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PlayerVsAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PlayerVsAlphaBetaAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PlayerVsReinforcementLearningAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* AIVsAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PlayerXButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PlayerOButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* RandomAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PlayerVsRandomAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* AlphaBetaAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* ReinforcementLearningAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PreviousAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* NextAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PreviousXAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* NextXAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PreviousOAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* NextOAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* ToggleSideButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* ConfirmAIButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* SelectedAIText;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* SelectedXAIText;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* SelectedOAIText;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* SelectedSideText;

    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* SelectionMenuPanel;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* LeftControllerText;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* RightControllerText;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* LeftControllerPreviousButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* LeftControllerNextButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* RightControllerPreviousButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* RightControllerNextButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* LeftRLAgentPanel;

    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* RightRLAgentPanel;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* LeftRLAgentText;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* RightRLAgentText;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* LeftRLAgentPreviousButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* LeftRLAgentNextButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* RightRLAgentPreviousButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* RightRLAgentNextButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* MenuActionText;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* MenuActionPreviousButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* MenuActionNextButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* MainActionButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* MainActionButtonText;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* MenuWarningText;

    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* TrainingSettingsPanel;

    UPROPERTY(meta = (BindWidgetOptional))
    USpinBox* TrainingEpisodeSpinBox;

    UPROPERTY(meta = (BindWidgetOptional))
    USpinBox* LearningRateSpinBox;

    UPROPERTY(meta = (BindWidgetOptional))
    USpinBox* DiscountFactorSpinBox;

    UPROPERTY(meta = (BindWidgetOptional))
    USpinBox* ExplorationRateSpinBox;

    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* ModeSelectPanel;

    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* SideSelectPanel;

    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* AISelectPanel;

    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* BoardPanel;

    ETicTacToeMatchMode PendingMatchMode = ETicTacToeMatchMode::PlayerVsPlayer;
    ETileState PendingHumanSide = ETileState::X;
    ETicTacToeAIType PendingAIType = ETicTacToeAIType::AlphaBeta;
    ETicTacToeAIType PendingXAIType = ETicTacToeAIType::AlphaBeta;
    ETicTacToeAIType PendingOAIType = ETicTacToeAIType::AlphaBeta;
    ETileState PendingAISelectionSide = ETileState::X;
    ETicTacToeControllerType LeftControllerType = ETicTacToeControllerType::Human;
    ETicTacToeControllerType RightControllerType = ETicTacToeControllerType::Human;
    ETicTacToeRLAgentSlot LeftRLAgentSlot = ETicTacToeRLAgentSlot::Slot1;
    ETicTacToeRLAgentSlot RightRLAgentSlot = ETicTacToeRLAgentSlot::Slot1;
    ETicTacToeMenuAction CurrentMenuAction = ETicTacToeMenuAction::Play;
    FTicTacToeRLTrainingSettings PendingTrainingSettings;

    UFUNCTION()
    void OnTileButton0Clicked();

    UFUNCTION()
    void OnTileButton1Clicked();

    UFUNCTION()
    void OnTileButton2Clicked();

    UFUNCTION()
    void OnTileButton3Clicked();

    UFUNCTION()
    void OnTileButton4Clicked();

    UFUNCTION()
    void OnTileButton5Clicked();

    UFUNCTION()
    void OnTileButton6Clicked();

    UFUNCTION()
    void OnTileButton7Clicked();

    UFUNCTION()
    void OnTileButton8Clicked();

    UFUNCTION()
    void OnRestartClicked();

    UFUNCTION()
    void OnPlayerVsPlayerClicked();

    UFUNCTION()
    void OnPlayerVsAIClicked();

    UFUNCTION()
    void OnPlayerVsAlphaBetaAIClicked();

    UFUNCTION()
    void OnPlayerVsReinforcementLearningAIClicked();

    UFUNCTION()
    void OnAIVsAIClicked();

    UFUNCTION()
    void OnPlayerXClicked();

    UFUNCTION()
    void OnPlayerOClicked();

    UFUNCTION()
    void OnRandomAIClicked();

    UFUNCTION()
    void OnPlayerVsRandomAIClicked();

    UFUNCTION()
    void OnAlphaBetaAIClicked();

    UFUNCTION()
    void OnReinforcementLearningAIClicked();

    UFUNCTION()
    void OnPreviousAIClicked();

    UFUNCTION()
    void OnNextAIClicked();

    UFUNCTION()
    void OnPreviousXAIClicked();

    UFUNCTION()
    void OnNextXAIClicked();

    UFUNCTION()
    void OnPreviousOAIClicked();

    UFUNCTION()
    void OnNextOAIClicked();

    UFUNCTION()
    void OnToggleSideClicked();

    UFUNCTION()
    void OnConfirmAIClicked();

    UFUNCTION()
    void OnLeftControllerPreviousClicked();

    UFUNCTION()
    void OnLeftControllerNextClicked();

    UFUNCTION()
    void OnRightControllerPreviousClicked();

    UFUNCTION()
    void OnRightControllerNextClicked();

    UFUNCTION()
    void OnLeftRLAgentPreviousClicked();

    UFUNCTION()
    void OnLeftRLAgentNextClicked();

    UFUNCTION()
    void OnRightRLAgentPreviousClicked();

    UFUNCTION()
    void OnRightRLAgentNextClicked();

    UFUNCTION()
    void OnMenuActionPreviousClicked();

    UFUNCTION()
    void OnMenuActionNextClicked();

    UFUNCTION()
    void OnMainActionClicked();

    UButton* GetRandomAIButton() const;
    void HandleTileClicked(int32 Index);
    void HandleAITypeSelected(ETicTacToeAIType AIType);
    bool ShouldDeployAISelectionImmediately() const;
    void DeployPendingAISelection();
    void ChangePendingAIType(int32 Direction);
    void ChangePendingXAIType(int32 Direction);
    void ChangePendingOAIType(int32 Direction);
    ETicTacToeAIType GetNextAIType(ETicTacToeAIType AIType, int32 Direction) const;
    FString GetAITypeLabel(ETicTacToeAIType AIType) const;
    void RefreshDeploymentSelectionUI();
    void CycleLeftControllerType(int32 Direction);
    void CycleRightControllerType(int32 Direction);
    void CycleMenuAction(int32 Direction);
    void CycleLeftRLAgentSlot(int32 Direction);
    void CycleRightRLAgentSlot(int32 Direction);
    ETicTacToeControllerType GetNextControllerType(ETicTacToeControllerType ControllerType, int32 Direction) const;
    ETicTacToeRLAgentSlot GetNextRLAgentSlot(ETicTacToeRLAgentSlot AgentSlot, int32 Direction) const;
    FString GetControllerTypeLabel(ETicTacToeControllerType ControllerType) const;
    FString GetRLAgentSlotLabel(ETicTacToeRLAgentSlot AgentSlot) const;
    FString GetRLAgentSaveSlotName(ETicTacToeRLAgentSlot AgentSlot) const;
    FString GetMenuActionLabel(ETicTacToeMenuAction MenuAction) const;
    void UpdateSelectionUI();
    bool ValidateTrainingSetup() const;
    void InitializeTrainingSettingsUI();
    void RefreshTrainingSettingsUI();
    FTicTacToeRLTrainingSettings GetTrainingSettingsFromUI() const;
    void SetTrainingSettingsControlsVisibility(bool bVisible) const;
    void StartMatch();
    void StartRLTrainingPlaceholder();
    void ShowModeSelect();
    void ShowSideSelect();
    void ShowAISelect();
    void ShowBoard();
    void SetPanelVisibility(UWidget* Panel, bool bVisible) const;
    void SetBoardControlsVisibility(bool bVisible) const;
    void SetModeControlsVisibility(bool bVisible) const;
    void SetSideControlsVisibility(bool bVisible) const;
    void SetAIControlsVisibility(bool bVisible) const;
    void SetDeploymentSwitchControlsVisibility(bool bVisible) const;
    void UpdateBoardUI();
};
