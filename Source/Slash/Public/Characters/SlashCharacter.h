#pragma once

#include "CoreMinimal.h"
#include "ECharacterState.h"
#include "GameFramework/Character.h"
#include "SlashCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class UAnimMontage;
struct FInputActionValue;

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

protected:
	ECharacterState CharacterState = ECharacterState::CS_Unarmed;
	
	UPROPERTY(BlueprintReadWrite, meta = ( AllowPrivateAccess = "true") )
	EActionState ActionState = EActionState::AS_Unoccupied;
	
	UPROPERTY(BlueprintReadOnly)
	UAnimInstance* AnimInstance;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnInteractZoneStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnInteractZoneEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	bool CanMove();

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	bool CanJump();
	void DoJump();
	bool CanAttack() const;
	bool CanBufferAttack() const;
	void Attack();
	void Equip();
	void Unequip();
	void Dodge();
	void Interact();
	
	void PlayAttackMontage();
	
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	
	UPROPERTY(VisibleInstanceOnly)
	bool CanInteract = false;
	
	UPROPERTY(VisibleInstanceOnly)
	bool GrabbedWeapon = false;
	
	UPROPERTY(VisibleInstanceOnly)
	bool IsWeaponEquipped = false;
	
	UPROPERTY(VisibleInstanceOnly)
	bool IsAttackBuffered = false;
	
	UPROPERTY(VisibleInstanceOnly)
	class AWeapon* InteractedWeapon;
	
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* InteractZone;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* MainCameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = Hair)
	UGroomComponent* Hair;
	
	UPROPERTY(EditDefaultsOnly, Category = Hair)
	UGroomComponent* Eyebrows;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DodgeAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipWeaponAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UnequipWeaponAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 1.f;
	
	// Animation montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;
	
	int AttackIndex = 0;
	const FName FirstAttackName = "Attack1";
	const FName SecondAttackName = "Attack2";

};
