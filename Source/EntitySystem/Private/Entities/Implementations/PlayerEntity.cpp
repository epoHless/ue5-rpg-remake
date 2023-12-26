#include "Entities/Implementations/PlayerEntity.h"

#include "Entities/State Management/Implementations/IdleState.h"
#include "Entities/State Management/Implementations/MovementState.h"

APlayerEntity::APlayerEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	IdleState = UIdleState::StaticClass();
	MovementState = UMovementState::StaticClass();

	const auto IdleObjectFinder = ConstructorHelpers::FObjectFinder<UFlipbookDataAsset>(TEXT("/Game/Core/Sprites/Characters/DA_PlayerFB.DA_PlayerFB"));
	FlipbookDataAsset = IdleObjectFinder.Object;
}

void APlayerEntity::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}