// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChallengeProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGEPROJECT_API AChallengeProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AChallengeProjectGameModeBase();

protected:
	virtual void BeginPlay() override;
};
