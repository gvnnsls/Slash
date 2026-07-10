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

float AItem::TransformedSin() const
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos() const
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

template <typename T>
T AItem::Avg(T first, T second)
{
	return (first + second) / 2;
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	
	float DeltaX = TransformedSin();
	float DeltaY = TransformedCos();
	float DeltaZ = 0.f;
	AddActorWorldOffset(FVector(DeltaX, DeltaY, DeltaZ));
	
	FVector actorForward = GetActorForwardVector();
	FVector actorPos = GetActorLocation();
	DRAW_SPHERE_SingleFrame(actorPos);
	DRAW_VECTOR_SingleFrame(actorPos, actorPos + actorForward * 100.f);

	FVector AvgVec = Avg<FVector>(GetActorLocation(), FVector::Zero());
	DRAW_DOT_SingleFrame(AvgVec);
}

