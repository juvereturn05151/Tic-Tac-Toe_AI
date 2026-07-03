/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "AddBackButtonToTicTacToeWidgetCommandlet.h"

#if WITH_EDITOR

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PanelWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
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

UPanelWidget* FindBoardButtonParent(UWidgetTree* WidgetTree, int32& OutInsertIndex)
{
    OutInsertIndex = INDEX_NONE;
    if (!WidgetTree)
    {
        return nullptr;
    }

    if (UWidget* RestartButtonSize = WidgetTree->FindWidget(TEXT("RestartButton_Size")))
    {
        int32 RestartButtonIndex = INDEX_NONE;
        UPanelWidget* RestartButtonParent = UWidgetTree::FindWidgetParent(RestartButtonSize, RestartButtonIndex);
        if (RestartButtonParent)
        {
            OutInsertIndex = RestartButtonIndex;
            return RestartButtonParent;
        }
    }

    return WidgetTree->FindWidget<UPanelWidget>(TEXT("BoardPanel"));
}

void ApplyButtonSlotPadding(UPanelSlot* PanelSlot)
{
    if (UHorizontalBoxSlot* HorizontalSlot = Cast<UHorizontalBoxSlot>(PanelSlot))
    {
        HorizontalSlot->SetPadding(FMargin(0.0f, 0.0f, 8.0f, 0.0f));
    }
    else if (UVerticalBoxSlot* VerticalSlot = Cast<UVerticalBoxSlot>(PanelSlot))
    {
        VerticalSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 8.0f));
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
        if (!Widget)
        {
            return;
        }

        const FName WidgetName = Widget->GetFName();
        if (!WidgetBlueprint->WidgetVariableNameToGuidMap.Contains(WidgetName))
        {
            WidgetBlueprint->WidgetVariableNameToGuidMap.Add(WidgetName, FGuid::NewGuid());
        }
    });
}

bool HasBackButton(UWidgetTree* WidgetTree)
{
    return WidgetTree && WidgetTree->FindWidget(TEXT("BackButton")) != nullptr;
}

void DumpWidgetTree(UWidgetTree* WidgetTree)
{
    if (!WidgetTree)
    {
        return;
    }

    WidgetTree->ForEachWidgetAndDescendants([WidgetTree](UWidget* Widget)
    {
        int32 ChildIndex = INDEX_NONE;
        UPanelWidget* Parent = UWidgetTree::FindWidgetParent(Widget, ChildIndex);
        UE_LOG(LogTemp, Display, TEXT("Widget: %s Class: %s Parent: %s Index: %d"),
            Widget ? *Widget->GetName() : TEXT("<null>"),
            Widget ? *Widget->GetClass()->GetName() : TEXT("<null>"),
            Parent ? *Parent->GetName() : TEXT("<none>"),
            ChildIndex);
    });
}
}

#endif

UAddBackButtonToTicTacToeWidgetCommandlet::UAddBackButtonToTicTacToeWidgetCommandlet()
{
    IsClient = false;
    IsEditor = true;
    IsServer = false;
    LogToConsole = true;
}

int32 UAddBackButtonToTicTacToeWidgetCommandlet::Main(const FString& Params)
{
#if WITH_EDITOR
    UWidgetBlueprint* WidgetBlueprint = LoadObject<UWidgetBlueprint>(nullptr, WidgetBlueprintPath);
    if (!WidgetBlueprint || !WidgetBlueprint->WidgetTree)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not load widget blueprint at %s."), WidgetBlueprintPath);
        return 1;
    }

    UWidgetTree* WidgetTree = WidgetBlueprint->WidgetTree;
    if (Params.Contains(TEXT("DumpOnly")))
    {
        DumpWidgetTree(WidgetTree);
        return 0;
    }

    if (Params.Contains(TEXT("VerifyOnly")))
    {
        const bool bHasBackButton = HasBackButton(WidgetTree);
        UE_LOG(LogTemp, Display, TEXT("Back button UI verification %s for %s."),
            bHasBackButton ? TEXT("succeeded") : TEXT("failed"),
            WidgetBlueprintPath);
        return bHasBackButton ? 0 : 1;
    }

    WidgetBlueprint->WidgetVariableNameToGuidMap.Remove(TEXT("BackButton_Size"));
    WidgetBlueprint->WidgetVariableNameToGuidMap.Remove(TEXT("BackButton"));
    WidgetBlueprint->WidgetVariableNameToGuidMap.Remove(TEXT("BackButtonText"));

    USizeBox* BackButtonSize = FindOrConstructWidget<USizeBox>(WidgetTree, TEXT("BackButton_Size"));
    UButton* BackButton = FindOrConstructWidget<UButton>(WidgetTree, TEXT("BackButton"));
    UTextBlock* BackButtonText = FindOrConstructWidget<UTextBlock>(WidgetTree, TEXT("BackButtonText"));
    if (!BackButtonSize || !BackButton || !BackButtonText)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not create BackButton widgets."));
        return 1;
    }

    BackButtonSize->SetWidthOverride(220.0f);
    BackButtonSize->SetHeightOverride(52.0f);
    BackButtonText->SetText(FText::FromString(TEXT("Back")));

    if (!BackButtonText->GetParent())
    {
        BackButton->AddChild(BackButtonText);
    }

    if (!BackButton->GetParent())
    {
        BackButtonSize->AddChild(BackButton);
    }

    if (!BackButtonSize->GetParent())
    {
        int32 InsertIndex = INDEX_NONE;
        UPanelWidget* ParentPanel = FindBoardButtonParent(WidgetTree, InsertIndex);
        if (!ParentPanel)
        {
            UE_LOG(LogTemp, Error, TEXT("Could not find a board panel to host BackButton."));
            return 1;
        }

        UPanelSlot* ButtonSlot = InsertIndex != INDEX_NONE
            ? ParentPanel->InsertChildAt(InsertIndex, BackButtonSize)
            : ParentPanel->AddChild(BackButtonSize);
        ApplyButtonSlotPadding(ButtonSlot);
    }

    RegisterMissingWidgetGuids(WidgetBlueprint);
    FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(WidgetBlueprint);
    FKismetEditorUtilities::CompileBlueprint(WidgetBlueprint);

    TArray<UPackage*> PackagesToSave;
    PackagesToSave.Add(WidgetBlueprint->GetOutermost());
    const bool bSaved = UEditorLoadingAndSavingUtils::SavePackages(PackagesToSave, false);

    UE_LOG(LogTemp, Display, TEXT("Back button UI %s %s."),
        bSaved ? TEXT("saved to") : TEXT("failed to save"),
        WidgetBlueprintPath);

    return bSaved ? 0 : 1;
#else
    UE_LOG(LogTemp, Error, TEXT("AddBackButtonToTicTacToeWidget requires editor support."));
    return 1;
#endif
}
