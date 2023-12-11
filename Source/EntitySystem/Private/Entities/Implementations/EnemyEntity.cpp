#include "Entities/Implementations/EnemyEntity.h"

AEnemyEntity::AEnemyEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyEntity::BeginPlay()
{
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