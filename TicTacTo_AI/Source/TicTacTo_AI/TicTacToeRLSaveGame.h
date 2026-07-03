/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TicTacToeTypes.h"
#include "TicTacToeRLSaveGame.generated.h"

USTRUCT(BlueprintType)
struct TICTACTO_AI_API FTicTacToeQValueArray
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TicTacToe|RL")
    TArray<float> Values;
};

UCLASS()
class TICTACTO_AI_API UTicTacToeRLSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TicTacToe|RL")
    FString AgentName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TicTacToe|RL")
    int32 EpisodesTrained = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TicTacToe|RL")
    TMap<FString, FTicTacToeQValueArray> SavedQTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TicTacToe|RL")
    FTicTacToeRLTrainingStats TrainingStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TicTacToe|RL")
    FTicTacToeRLTrainingSettings TrainingSettings;
};
