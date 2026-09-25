#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	CS_Unequipped UMETA(DisplayName = "Unequipped"),
	CS_EquippedOneHanded UMETA(DisplayName = "Equipped One Handed"),
	CS_EquippedTwoHanded UMETA(DisplayName = "Equipped Two Handed")
};
