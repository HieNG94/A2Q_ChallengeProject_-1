// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "MovingSphere.h"

// Sets default values
AMovingSphere::AMovingSphere()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a sphere that reacts to physics
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Set up visual mesh
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SphereMaterial(TEXT("/Game/StarterContent/Materials/M_Water_Lake.M_Water_Lake"));
	if (SphereVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}
	if (SphereMaterial.Succeeded())
	{
		VisualMesh->SetMaterial(0, SphereMaterial.Object);
	}

	// Particle system
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(VisualMesh);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	OurParticleSystem->SetRelativeScale3D(FVector(2.f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(VisualMesh);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = true; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void AMovingSphere::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMovingSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMovingSphere::Ignite()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}

