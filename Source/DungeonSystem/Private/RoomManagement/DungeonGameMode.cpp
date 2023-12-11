#include "RoomManagement/DungeonGameMode.h"

#include "Entities/Implementations/PlayerEntity.h"
#include "Managers/EntityController.h"

ADungeonGameMode::ADungeonGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = APlayerEntity::StaticClass();
	PlayerControllerClass = AEntityController::StaticClass();
}

void ADungeonGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ADungeonGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}