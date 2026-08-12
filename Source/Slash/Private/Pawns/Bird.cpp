// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

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

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 200.f;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

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
	// UE_LOG(LogTemp, Warning, TEXT("Value: x %f, y %f"), MovementVector.X, MovementVector.Y);

	if (MovementVector.Y != 0)
	{
		auto forward = GetActorForwardVector();
		AddMovementInput(forward, MovementVector.Y * 10);
	}

	if (MovementVector.X != 0)
	{
		// todo: x axis movement?
	}
	
}

void ABird::LookAround(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookVector = Value.Get<FVector2D>();
	// UE_LOG(LogTemp, Warning, TEXT("Value: x %f, y %f"), LookVector.X, LookVector.Y);
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
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

			// Look
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::LookAround);
		}
		
	}
	
}

