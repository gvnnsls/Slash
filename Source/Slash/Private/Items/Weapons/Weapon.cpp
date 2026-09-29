// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"

void AWeapon::OnSphereStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereStartOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ItemState != EItemState::EIS_Hovering)
		return;
	
	float DeltaZ = TransformedSin();
	AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
	
	DeltaRot += DeltaTime * RotSpeed;
	SetActorRotation(FRotator(0.f, DeltaRot, 0.f));
}

void AWeapon::EquipWeapon()
{
	ItemState = EItemState::EIS_Equipped;
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
