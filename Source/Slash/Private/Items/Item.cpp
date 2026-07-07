// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "InputState.h"
#include "Slash/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}
void AItem::BeginPlay()
{
	Super::BeginPlay();
}
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float MovementRate = 100.f;
	float RotationRate = 85.f;
	FVector actorForward = GetActorForwardVector();
	FVector actorPos = GetActorLocation();

	AddActorWorldOffset(actorForward * MovementRate * DeltaTime);
	AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
	DRAW_SPHERE_SingleFrame(actorPos);
	DRAW_VECTOR_SingleFrame(actorPos, actorPos + actorForward * 100.f)
}

