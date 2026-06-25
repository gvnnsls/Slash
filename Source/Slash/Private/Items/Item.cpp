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
}
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

