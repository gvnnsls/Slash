// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation(){
	Super::NativeInitializeAnimation();
	
	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
	if (SlashCharacter)
	{
		SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (SlashCharacterMovement)
	{
		FVector velocity = SlashCharacterMovement->Velocity;
		GroundSpeed = UKismetMathLibrary::VSizeXY(velocity);
		VerticalSpeed = velocity.Z;
		CharacterState = SlashCharacter->GetCharacterState();
	}
	
}
