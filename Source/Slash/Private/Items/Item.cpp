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

	RunningTime += DeltaTime;
	
	float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

	AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
	
	FVector actorForward = GetActorForwardVector();
	FVector actorPos = GetActorLocation();
	DRAW_SPHERE_SingleFrame(actorPos);
	DRAW_VECTOR_SingleFrame(actorPos, actorPos + actorForward * 100.f)
}

