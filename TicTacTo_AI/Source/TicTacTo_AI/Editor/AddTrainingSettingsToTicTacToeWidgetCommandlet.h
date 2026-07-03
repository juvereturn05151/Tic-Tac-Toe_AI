/*
 * Copyright (c) 2026 Ju-ve Chankasemporn
 * E-mail: juvereturn@gmail.com
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "AddTrainingSettingsToTicTacToeWidgetCommandlet.generated.h"

UCLASS()
class TICTACTO_AI_API UAddTrainingSettingsToTicTacToeWidgetCommandlet : public UCommandlet
{
    GENERATED_BODY()

public:
    UAddTrainingSettingsToTicTacToeWidgetCommandlet();

    virtual int32 Main(const FString& Params) override;
};
