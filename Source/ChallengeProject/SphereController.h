// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SphereController.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGEPROJECT_API ASphereController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASphereController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void ChangeCameraAscending();
	void ChangeCameraDescending();
	void ChangeCameraCooldown();
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void ParticleToggle();

private:
	const float SmoothBlendTime = 0.5f;
	TArray<AActor*>FoundActors;
	int8 index = 0;
	float Speed = 2.f;		// Speed of the sphere, max at 2.f
	FVector CurrentVelocity;
	bool ButtonCooldown = false;
	FTimerHandle ChangeCamCd;
};
