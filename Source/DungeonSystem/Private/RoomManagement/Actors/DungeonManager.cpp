﻿#include "RoomManagement/Actors/DungeonManager.h"

#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "FunctionLibraries/ExtensionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/RoomSubsystem.h"

ADungeonManager::ADungeonManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADungeonManager::BeginPlay()
{
	Super::BeginPlay();

	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
	RoomSubsystem->OnRoomChanged.AddDynamic(this, &ADungeonManager::ChangeTileset);
}

void ADungeonManager::ChangeTileset(FRoomInstance Room)
{
	TilemapActor->GetRenderComponent()->SetTileMap(Room.TileMap ? Room.TileMap : BaseTileMap);
}
