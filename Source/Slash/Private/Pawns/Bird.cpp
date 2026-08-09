// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"

ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);
	
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMeshComponent"));
	BirdMesh->SetupAttachment(GetRootComponent());

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}
void ABird::BeginPlay()
{
	Super::BeginPlay();
}

void ABird::MoveForward(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
}

float ABird::TransformedSin() const
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	float DeltaZ = TransformedSin();
	AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
}

