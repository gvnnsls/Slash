// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"

#include "Characters/SlashCharacter.h"

void AWeapon::OnSphereStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereStartOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	AWeapon::EquipWeaponToActor(OtherActor);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isEquipped)
		return;
	
	float DeltaZ = TransformedSin();
	AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
	
	DeltaRot += DeltaTime * RotSpeed;
	SetActorRotation(FRotator(0.f, DeltaRot, 0.f));
}

void AWeapon::EquipWeaponToActor(AActor* OtherActor)
{
	if (isEquipped)
		return;
	
	ASlashCharacter* slashChara = Cast<ASlashCharacter>(OtherActor);
	if (!slashChara)
		return;
	
	const auto& charaMesh = slashChara->GetMesh();
	ItemMesh->AttachToComponent(charaMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightHandSocket"));
	
	isEquipped = true;
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
