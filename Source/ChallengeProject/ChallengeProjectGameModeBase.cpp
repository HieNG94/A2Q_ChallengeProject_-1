// Copyright Epic Games, Inc. All Rights Reserved.


#include "MovingSphere.h"
#include "SphereController.h"
#include "Math/UnrealMathUtility.h"
#include "ChallengeProjectGameModeBase.h"

AChallengeProjectGameModeBase::AChallengeProjectGameModeBase()
{
	PlayerControllerClass = ASphereController::StaticClass();
}

void AChallengeProjectGameModeBase::BeginPlay()
{
	int8 SpawnNum = FMath::RandRange(2, 6);
	int8 i = 0;

	while (i < SpawnNum)
	{
		float X = FMath::RandRange(70, 1840);
		float Y = FMath::RandRange(-740, 1010);
		FVector SpawnLocation = FVector(X, Y, 85.f);

		GetWorld()->SpawnActor(AMovingSphere::StaticClass(), &SpawnLocation);
		i++;
	}
}
