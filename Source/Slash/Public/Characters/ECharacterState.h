#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	CS_Unarmed UMETA(DisplayName = "Unarmed"),
	CS_EquippedOneHanded UMETA(DisplayName = "Equipped One Handed"),
	CS_EquippedTwoHanded UMETA(DisplayName = "Equipped Two Handed")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	AS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	AS_Attacking UMETA(DisplayName = "Attacking"),
};
