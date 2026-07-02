/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TicTacToeBoardWidget.generated.h"

class UButton;
class UTextBlock;

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

    void HandleTileClicked(int32 Index);
    void UpdateBoardUI();
};
