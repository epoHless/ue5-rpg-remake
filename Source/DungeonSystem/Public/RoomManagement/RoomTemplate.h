﻿#pragma once

#include "PaperTileMap.h"
#include "RoomTemplate.generated.h"

USTRUCT(BlueprintType)
struct DUNGEONSYSTEM_API FRoomTemplate : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	UPaperTileMap* TileMap;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System", meta = (MustImplement = "Spawnable"))
	TArray<TSubclassOf<UObject>> SpawnableEntities;
};