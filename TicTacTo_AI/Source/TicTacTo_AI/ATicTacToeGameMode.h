/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ATicTacToeGameMode.generated.h"

UENUM(BlueprintType)
enum class ETileState : uint8
{
    Empty UMETA(DisplayName = "Empty"),
    X     UMETA(DisplayName = "X"),
    O     UMETA(DisplayName = "O")
};

UCLASS()
class TICTACTO_AI_API ATicTacToeGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATicTacToeGameMode();

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    TArray<ETileState> Board;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    ETileState CurrentPlayer;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    bool bGameOver;

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    ETileState Winner;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    bool MakeMove(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void ResetGame();

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    ETileState GetTileState(int32 Index) const;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    FString GetTileText(int32 Index) const;

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    FString GetStatusText() const;

private:
    bool CheckWinner(ETileState Player) const;
    bool CheckDraw() const;
    void SwitchTurn();
};
