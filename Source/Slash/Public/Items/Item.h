// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SLASH_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly)
	float RunningTime;
	
	UPROPERTY(EditInstanceOnly)
	float Amplitude = 0.25f;
	
	UPROPERTY(EditInstanceOnly)
	float TimeConstant = 5.f;
};
