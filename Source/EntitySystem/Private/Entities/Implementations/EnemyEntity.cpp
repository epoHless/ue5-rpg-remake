#include "Entities/Implementations/EnemyEntity.h"

#include "Entities/State Management/Implementations/AttackState.h"
#include "Entities/State Management/Implementations/EnemyMovementState.h"
#include "Entities/State Management/Implementations/IdleState.h"

AEnemyEntity::AEnemyEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	IdleState = UIdleState::StaticClass();
	MovementState = UEnemyMovementState::StaticClass();
	AttackState = UAttackState::StaticClass();
}

void AEnemyEntity::BeginPlay()
{
	if (CurrentState == nullptr)
	{
		CurrentState = NewObject<UIdleState>();
	}
	
	Super::BeginPlay();	
}

void AEnemyEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}