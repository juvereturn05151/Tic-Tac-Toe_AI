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

UENUM(BlueprintType)
enum class ETicTacToePlayMode : uint8
{
    PlayerVsPlayer                  UMETA(DisplayName = "Player vs Player"),
    PlayerVsRandomAI                UMETA(DisplayName = "Player vs AI (Random)"),
    PlayerVsAlphaBetaAI             UMETA(DisplayName = "Player vs AI (Alpha-Beta)"),
    PlayerVsReinforcementLearningAI UMETA(DisplayName = "Player vs AI (Reinforcement Learning)")
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

    UPROPERTY(BlueprintReadOnly, Category = "TicTacToe")
    ETicTacToePlayMode PlayMode;

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

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void SetPlayMode(ETicTacToePlayMode NewPlayMode);

    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    ETicTacToePlayMode GetPlayMode() const;

private:
    bool MakeMoveForCurrentPlayer(int32 Index);
    void MakeRandomAIMove();
    void MakeAlphaBetaAIMove();
    void MakeReinforcementLearningAIMove();
    bool IsAIMode() const;
    int32 Minimax(bool bIsMaximizing, int32 Depth, int32 Alpha, int32 Beta);
    bool CheckWinner(ETileState Player) const;
    bool CheckDraw() const;
    void SwitchTurn();
};
