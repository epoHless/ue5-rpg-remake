#include "Entities/Implementations/EnemyEntity.h"

AEnemyEntity::AEnemyEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyEntity::BeginPlay()
{	
	Super::BeginPlay();

	const FVector Location = GetActorLocation();
	SetActorLocation(FVector(Location.X, Location.Y, 15));
}

void AEnemyEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}