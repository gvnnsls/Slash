// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

// Forward declaration: tells compiler this class exists without including the full header.
// Header will be included in .cpp
class UCapsuleComponent;
class USkeletalMeshComponent;

UCLASS()
class SLASH_API ABird : public APawn
{
	GENERATED_BODY()

public:
	ABird();
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void MoveForward(float value);

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Sine Constants")
	float Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Sine Constants")
	float RotSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Sine Constants")
	float TimeConstant = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DeltaRot = 0.f;

	UFUNCTION(BlueprintPure)
	float TransformedSin() const;
};
