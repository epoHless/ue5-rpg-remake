#include "Entities/Implementations/EnemyEntity.h"
#include "Kismet/GameplayStatics.h"

AEnemyEntity::AEnemyEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupComponents();
}

void AEnemyEntity::BeginPlay()
{
	PlayerPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	Super::BeginPlay();
}