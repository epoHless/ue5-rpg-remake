#include "Actors/EntityManager.h"

#include "FunctionLibraries/ExtensionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/RoomSubsystem.h"

AEntityManager::AEntityManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEntityManager::BeginPlay()
{
	Super::BeginPlay();

	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
	RoomSubsystem->OnRoomChanged.AddDynamic(this, &AEntityManager::ToggleEnemies);
}

void AEntityManager::ToggleEnemies(const FRoomInstance& Room)
{
	
}