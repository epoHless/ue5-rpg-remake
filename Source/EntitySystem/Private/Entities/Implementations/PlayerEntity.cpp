#include "Entities/Implementations/PlayerEntity.h"

#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerEntity::APlayerEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	const auto IdleObjectFinder = ConstructorHelpers::FObjectFinder<UPaperFlipbook>(TEXT("/Game/Core/Sprites/Characters/Player/Idle/knight_m_idle_anim_f4.knight_m_idle_anim_f4"));
	IdleFlipbook = IdleObjectFinder.Object;

	const auto RunObjectFinder = ConstructorHelpers::FObjectFinder<UPaperFlipbook>(TEXT("/Game/Core/Sprites/Characters/Player/Run/knight_m_run_anim_f0.knight_m_run_anim_f0"));
	RunFlipbook = RunObjectFinder.Object;
	
	GetSprite()->SetFlipbook(IdleFlipbook);
	GetSprite()->SetRelativeRotation(FRotator(0,0,-90));

	GetCapsuleComponent()->SetCapsuleRadius(5);
	GetCapsuleComponent()->SetCapsuleHalfHeight(10);

	GetCharacterMovement()->GravityScale = 0;
}

void APlayerEntity::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetSprite()->SetFlipbook(GetMovementComponent()->Velocity != FVector::ZeroVector ? RunFlipbook : IdleFlipbook);
}

void APlayerEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}