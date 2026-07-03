/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "AddTrainingSettingsToTicTacToeWidgetCommandlet.h"

#if WITH_EDITOR

#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PanelWidget.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "FileHelpers.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "WidgetBlueprint.h"

namespace
{
constexpr const TCHAR* WidgetBlueprintPath = TEXT("/Game/Widget/WBP_TicTacToe.WBP_TicTacToe");

template <typename WidgetT>
WidgetT* FindOrConstructWidget(UWidgetTree* WidgetTree, const FName WidgetName)
{
    if (!WidgetTree)
    {
        return nullptr;
    }

    if (WidgetT* ExistingWidget = WidgetTree->FindWidget<WidgetT>(WidgetName))
    {
        return ExistingWidget;
    }

    return WidgetTree->ConstructWidget<WidgetT>(WidgetT::StaticClass(), WidgetName);
}

UTextBlock* CreateLabel(UWidgetTree* WidgetTree, const FName WidgetName, const FString& Label)
{
    UTextBlock* LabelText = FindOrConstructWidget<UTextBlock>(WidgetTree, WidgetName);
    if (LabelText)
    {
        LabelText->SetText(FText::FromString(Label));
    }

    return LabelText;
}

USpinBox* CreateSpinBox(UWidgetTree* WidgetTree, const FName WidgetName, float Value, float MinValue, float MaxValue, float MaxSliderValue)
{
    USpinBox* SpinBox = FindOrConstructWidget<USpinBox>(WidgetTree, WidgetName);
    if (SpinBox)
    {
        SpinBox->SetMinValue(MinValue);
        SpinBox->SetMaxValue(MaxValue);
        SpinBox->SetMinSliderValue(MinValue);
        SpinBox->SetMaxSliderValue(MaxSliderValue);
        SpinBox->SetValue(Value);
    }

    return SpinBox;
}

void AddRow(UWidgetTree* WidgetTree, UVerticalBox* ParentPanel, const FName RowName, const FName LabelName, const FString& Label, USpinBox* SpinBox)
{
    if (!WidgetTree || !ParentPanel || !SpinBox)
    {
        return;
    }

    UHorizontalBox* Row = FindOrConstructWidget<UHorizontalBox>(WidgetTree, RowName);
    if (!Row)
    {
        return;
    }

    if (!Row->GetParent())
    {
        UVerticalBoxSlot* RowSlot = ParentPanel->AddChildToVerticalBox(Row);
        if (RowSlot)
        {
            RowSlot->SetPadding(FMargin(0.0f, 3.0f));
        }
    }

    UTextBlock* LabelText = CreateLabel(WidgetTree, LabelName, Label);
    if (LabelText && !LabelText->GetParent())
    {
        UHorizontalBoxSlot* LabelSlot = Row->AddChildToHorizontalBox(LabelText);
        if (LabelSlot)
        {
            LabelSlot->SetPadding(FMargin(0.0f, 0.0f, 12.0f, 0.0f));
        }
    }

    if (!SpinBox->GetParent())
    {
        Row->AddChildToHorizontalBox(SpinBox);
    }
}

UPanelWidget* FindTrainingPanelParent(UWidgetTree* WidgetTree)
{
    if (!WidgetTree)
    {
        return nullptr;
    }

    if (UPanelWidget* BottomActionPanel = WidgetTree->FindWidget<UPanelWidget>(TEXT("BottomActionPanel")))
    {
        return BottomActionPanel;
    }

    if (UPanelWidget* SelectionMenuPanel = WidgetTree->FindWidget<UPanelWidget>(TEXT("SelectionMenuPanel")))
    {
        return SelectionMenuPanel;
    }

    return Cast<UPanelWidget>(WidgetTree->RootWidget);
}

void AttachTrainingPanel(UWidgetTree* WidgetTree, UPanelWidget* Parent, UVerticalBox* TrainingPanel)
{
    if (!WidgetTree || !Parent || !TrainingPanel || TrainingPanel->GetParent())
    {
        return;
    }

    int32 InsertIndex = Parent->GetChildrenCount();
    if (UWidget* MainActionButton = WidgetTree->FindWidget(TEXT("MainActionButton")))
    {
        int32 MainActionIndex = INDEX_NONE;
        if (UWidgetTree::FindWidgetParent(MainActionButton, MainActionIndex) == Parent && MainActionIndex != INDEX_NONE)
        {
            InsertIndex = MainActionIndex;
        }
    }

    UPanelSlot* PanelSlot = Parent->InsertChildAt(InsertIndex, TrainingPanel);
    if (UVerticalBoxSlot* VerticalSlot = Cast<UVerticalBoxSlot>(PanelSlot))
    {
        VerticalSlot->SetPadding(FMargin(0.0f, 8.0f));
    }
}

void RegisterMissingWidgetGuids(UWidgetBlueprint* WidgetBlueprint)
{
    if (!WidgetBlueprint || !WidgetBlueprint->WidgetTree)
    {
        return;
    }

    WidgetBlueprint->WidgetTree->ForEachWidgetAndDescendants([WidgetBlueprint](UWidget* Widget)
    {
        if (Widget && !WidgetBlueprint->WidgetVariableNameToGuidMap.Contains(Widget->GetFName()))
        {
            WidgetBlueprint->OnVariableAdded(Widget->GetFName());
        }
    });
}

bool HasTrainingSettingsWidgets(UWidgetTree* WidgetTree)
{
    if (!WidgetTree)
    {
        return false;
    }

    const FName RequiredWidgetNames[] =
    {
        TEXT("TrainingSettingsPanel"),
        TEXT("TrainingEpisodeSpinBox"),
        TEXT("LearningRateSpinBox"),
        TEXT("DiscountFactorSpinBox"),
        TEXT("ExplorationRateSpinBox")
    };

    for (const FName WidgetName : RequiredWidgetNames)
    {
        if (!WidgetTree->FindWidget(WidgetName))
        {
            UE_LOG(LogTemp, Error, TEXT("Missing training settings widget: %s"), *WidgetName.ToString());
            return false;
        }
    }

    return true;
}
}

#endif

UAddTrainingSettingsToTicTacToeWidgetCommandlet::UAddTrainingSettingsToTicTacToeWidgetCommandlet()
{
    IsClient = false;
    IsEditor = true;
    IsServer = false;
    LogToConsole = true;
}

int32 UAddTrainingSettingsToTicTacToeWidgetCommandlet::Main(const FString& Params)
{
#if WITH_EDITOR
    UWidgetBlueprint* WidgetBlueprint = LoadObject<UWidgetBlueprint>(nullptr, WidgetBlueprintPath);
    if (!WidgetBlueprint || !WidgetBlueprint->WidgetTree)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not load widget blueprint at %s."), WidgetBlueprintPath);
        return 1;
    }

    UWidgetTree* WidgetTree = WidgetBlueprint->WidgetTree;
    if (Params.Contains(TEXT("VerifyOnly")))
    {
        const bool bHasTrainingSettingsWidgets = HasTrainingSettingsWidgets(WidgetTree);
        UE_LOG(LogTemp, Display, TEXT("Training settings UI verification %s for %s."),
            bHasTrainingSettingsWidgets ? TEXT("succeeded") : TEXT("failed"),
            WidgetBlueprintPath);
        return bHasTrainingSettingsWidgets ? 0 : 1;
    }

    UPanelWidget* ParentPanel = FindTrainingPanelParent(WidgetTree);
    if (!ParentPanel)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find a panel to host TrainingSettingsPanel."));
        return 1;
    }

    UVerticalBox* TrainingPanel = FindOrConstructWidget<UVerticalBox>(WidgetTree, TEXT("TrainingSettingsPanel"));
    if (!TrainingPanel)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not create TrainingSettingsPanel."));
        return 1;
    }

    AttachTrainingPanel(WidgetTree, ParentPanel, TrainingPanel);

    AddRow(WidgetTree, TrainingPanel, TEXT("TrainingEpisodeRow"), TEXT("TrainingEpisodeLabel"), TEXT("Episodes"),
        CreateSpinBox(WidgetTree, TEXT("TrainingEpisodeSpinBox"), 10000.0f, 1.0f, 1000000.0f, 100000.0f));
    AddRow(WidgetTree, TrainingPanel, TEXT("LearningRateRow"), TEXT("LearningRateLabel"), TEXT("Learning Rate"),
        CreateSpinBox(WidgetTree, TEXT("LearningRateSpinBox"), 0.1f, 0.0f, 1.0f, 1.0f));
    AddRow(WidgetTree, TrainingPanel, TEXT("DiscountFactorRow"), TEXT("DiscountFactorLabel"), TEXT("Discount Factor"),
        CreateSpinBox(WidgetTree, TEXT("DiscountFactorSpinBox"), 0.95f, 0.0f, 1.0f, 1.0f));
    AddRow(WidgetTree, TrainingPanel, TEXT("ExplorationRateRow"), TEXT("ExplorationRateLabel"), TEXT("Exploration Rate"),
        CreateSpinBox(WidgetTree, TEXT("ExplorationRateSpinBox"), 1.0f, 0.0f, 1.0f, 1.0f));

    RegisterMissingWidgetGuids(WidgetBlueprint);
    FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(WidgetBlueprint);
    FKismetEditorUtilities::CompileBlueprint(WidgetBlueprint);

    TArray<UPackage*> PackagesToSave;
    PackagesToSave.Add(WidgetBlueprint->GetOutermost());
    const bool bSaved = UEditorLoadingAndSavingUtils::SavePackages(PackagesToSave, false);

    UE_LOG(LogTemp, Display, TEXT("Training settings UI %s %s."),
        bSaved ? TEXT("saved to") : TEXT("failed to save"),
        WidgetBlueprintPath);

    return bSaved ? 0 : 1;
#else
    UE_LOG(LogTemp, Error, TEXT("AddTrainingSettingsToTicTacToeWidget requires editor support."));
    return 1;
#endif
}
