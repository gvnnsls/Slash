// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"

ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);
	
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMeshComponent"));
	BirdMesh->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("BirdFloatingMovement"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}
void ABird::BeginPlay()
{
	Super::BeginPlay();
}

void ABird::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Value: x %f, y %f"), MovementVector.X, MovementVector.Y);

	if (MovementVector.Y != 0)
	{
		auto forward = GetActorForwardVector();
		AddMovementInput(forward, MovementVector.Y * 10);
	}

	if (MovementVector.X != 0)
	{
		// AddActorWorldRotation()
	}
	

	
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
	// AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

			// Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		}
		
	}
	
}

