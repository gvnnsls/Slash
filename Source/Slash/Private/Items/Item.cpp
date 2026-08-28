// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "InputState.h"
#include "Components/SphereComponent.h"
#include "Slash/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereColl"));
	SphereCollider->SetupAttachment(GetRootComponent());
}
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
}

float AItem::TransformedSin() const
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos() const
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	const auto otherActorName = OtherActor->GetName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, otherActorName);
	}
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

