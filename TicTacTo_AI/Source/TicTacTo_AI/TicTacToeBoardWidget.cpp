/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#include "TicTacToeBoardWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ATicTacToeGameMode.h"

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

    UpdateBoardUI();
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
    UpdateBoardUI();
}

void UTicTacToeBoardWidget::OnPlayerVsPlayerClicked()
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    TicTacToeGameMode->SetPlayMode(ETicTacToePlayMode::PlayerVsPlayer);
    UpdateBoardUI();
}

void UTicTacToeBoardWidget::OnPlayerVsAIClicked()
{
    ATicTacToeGameMode* TicTacToeGameMode = Cast<ATicTacToeGameMode>(UGameplayStatics::GetGameMode(this));
    if (!TicTacToeGameMode)
    {
        return;
    }

    TicTacToeGameMode->SetPlayMode(ETicTacToePlayMode::PlayerVsAI);
    UpdateBoardUI();
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
        const FString ModeLabel = TicTacToeGameMode->GetPlayMode() == ETicTacToePlayMode::PlayerVsAI
            ? TEXT("Player vs AI")
            : TEXT("Player vs Player");
        ModeText->SetText(FText::FromString(ModeLabel));
    }
}
