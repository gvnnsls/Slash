// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "InputState.h"
#include "Slash/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;
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

	float DeltaZ = TransformedSin();
	AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
	
	DeltaRot += DeltaTime * RotSpeed;
	SetActorRotation(FRotator(0.f, DeltaRot, 0.f));
	// adds constant rotation/delta rotation, makes it keep rotating constantly, doesn't need to be in Tick
	// AddActorLocalRotation(FRotator(0.f, DeltaRot, 0.f));
}

