

#include "Characters/SlashCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GroomComponent.h"
#include "Items/Weapons/Weapon.h"

ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->RotationRate.Roll = 1000;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	
	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCameraComponent"));
	MainCameraComponent->SetupAttachment(SpringArmComponent);
	
	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");
	
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");
	
	InteractZone = CreateDefaultSubobject<USphereComponent>(TEXT("InteractZone"));
	InteractZone->SetupAttachment(GetRootComponent());

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InteractZone->OnComponentBeginOverlap.AddDynamic(this, &ASlashCharacter::OnInteractZoneStartOverlap);
	InteractZone->OnComponentEndOverlap.AddDynamic(this, &ASlashCharacter::OnInteractZoneEndOverlap);
}

void ASlashCharacter::OnInteractZoneStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWeapon* weapon = Cast<AWeapon>(OtherActor);
	if (weapon)
	{
		InteractedItem = weapon;
		CanInteract = true;
	}
}

void ASlashCharacter::OnInteractZoneEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CanInteract = false;
	InteractedItem = nullptr;
}

void ASlashCharacter::Move(const FInputActionValue& value)
{
	// input is a Vector2D
	// Note: the input vector uses X for left and right (A or D) and Y for up and down (W or S), not related to spacial coordinates
	// Meanwhile in unreal coordinate system, Forward is the X vector and Right is the Y vector, 
	// which causes confusion when translating from input vector to actual movement
	FVector2D MovementVector = value.Get<FVector2D>();

	if (MovementVector.Y != 0)
	{
		const FRotator ControlRot = GetControlRotation();
		const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		
		AddMovementInput(Direction, MovementVector.Y * MovementSpeed);
	}

	if (MovementVector.X != 0)
	{
		const FRotator ControlRot = GetControlRotation();
		const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Direction, MovementVector.X * MovementSpeed);
	}
}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookVector = Value.Get<FVector2D>();
	// UE_LOG(LogTemp, Warning, TEXT("Value: x %f, y %f"), LookVector.X, LookVector.Y);
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ASlashCharacter::DoJump()
{
	Jump();
}

void ASlashCharacter::Attack()
{
}

void ASlashCharacter::Equip()
{
	if (GrabbedWeapon)
		return;
	
	if (!InteractedItem)
		return;
	
	const auto& ItemMesh = InteractedItem->GetItemMesh();
	ItemMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightHandSocket"));
	
	GrabbedWeapon = true;
	IsWeaponEquipped = true;
}

void ASlashCharacter::Unequip()
{
}

void ASlashCharacter::Dodge()
{
}

void ASlashCharacter::Interact()
{
	if (!CanInteract)
		return;
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

			// Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
			// Camera/look
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
			// Jump
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASlashCharacter::DoJump);
			// Attack
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);
			// Equip
			EnhancedInputComponent->BindAction(EquipWeaponAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Equip);
			// Unequip
			EnhancedInputComponent->BindAction(UnequipWeaponAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Unequip);
			// Dodge
			EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge);
			// Interaction
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Interact);
		}
		
	}
}

