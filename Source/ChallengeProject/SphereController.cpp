// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingSphere.h"
#include "ChallengeProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "SphereController.h"

ASphereController::ASphereController()
{
}

void ASphereController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMovingSphere::StaticClass(), FoundActors);

	this->SetViewTarget(FoundActors[index]);
}

void ASphereController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASphereController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ASphereController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASphereController::MoveRight);

	InputComponent->BindAction("ChangeCamAsc", IE_Pressed, this, &ASphereController::ChangeCameraAscending);
	InputComponent->BindAction("ChangeCamDesc", IE_Pressed, this, &ASphereController::ChangeCameraDescending);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ASphereController::ParticleToggle);
}

void ASphereController::ChangeCameraAscending()
{
	if (!ButtonCooldown)
	{
		ButtonCooldown = true;
		if (index == FoundActors.Num() - 1)
		{
			index = 0;
		}
		else
		{
			index++;
		}
		this->SetViewTargetWithBlend(FoundActors[index], SmoothBlendTime);
		GetWorld()->GetTimerManager().SetTimer(ChangeCamCd, this, &ASphereController::ChangeCameraCooldown, SmoothBlendTime, false);
	}
}

void ASphereController::ChangeCameraDescending()
{
	if (!ButtonCooldown)
	{
		ButtonCooldown = true;
		if (index == 0)
		{
			index = FoundActors.Num() - 1;
		}
		else
		{
			index--;
		}
		this->SetViewTargetWithBlend(FoundActors[index], SmoothBlendTime);
		GetWorld()->GetTimerManager().SetTimer(ChangeCamCd, this, &ASphereController::ChangeCameraCooldown, SmoothBlendTime, false);
	}
}

void ASphereController::ChangeCameraCooldown()
{
	ButtonCooldown = false;
	GetWorld()->GetTimerManager().ClearTimer(ChangeCamCd);
}

void ASphereController::MoveForward(float Axis)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(Axis, -1.0f, 1.0f) * Speed;

	FVector NewLocation = FoundActors[index]->GetActorLocation() + CurrentVelocity;
	FoundActors[index]->SetActorLocation(NewLocation, true);

}

void ASphereController::MoveRight(float Axis)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(Axis, -1.0f, 1.0f) * Speed;

	FVector NewLocation = FoundActors[index]->GetActorLocation() + CurrentVelocity;
	FoundActors[index]->SetActorLocation(NewLocation, true);

}

void ASphereController::ParticleToggle()
{
	AMovingSphere* SphereActor = Cast<AMovingSphere>(FoundActors[index]);
	if (SphereActor)
	{
		SphereActor->Ignite();
	}
}
