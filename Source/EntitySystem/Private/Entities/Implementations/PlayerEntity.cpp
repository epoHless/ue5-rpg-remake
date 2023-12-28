#include "Entities/Implementations/PlayerEntity.h"

APlayerEntity::APlayerEntity()
{	
	PrimaryActorTick.bCanEverTick = true;

	const auto DataObjectFinder = ConstructorHelpers::FObjectFinder<UEntityDataAsset>(TEXT("/Script/EntitySystem.EntityDataAsset'/Game/Core/Data/Player/PlayerData.PlayerData'"));
	EntityDataAsset = DataObjectFinder.Object;

	SetupEntity(EntityDataAsset);
	SetupComponents();
}

void APlayerEntity::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}