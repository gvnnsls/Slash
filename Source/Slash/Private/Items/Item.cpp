// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}
void AItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BEGIN PLAY CALLED!"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Blue, FString("Item OnScreenMessage!"));
	}
}
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Warning, TEXT("Dt: %f"), DeltaTime);
	//
	// if (GEngine)
	// {
	// 	FString name = GetName();
	// 	FString msg = FString::Printf(TEXT("Dt: %f, item name: %s"), DeltaTime, *name);
	// 	GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Blue, msg);
	// }
}

