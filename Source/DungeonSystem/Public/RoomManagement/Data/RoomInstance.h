#pragma once

#include "CoreMinimal.h"
#include "Entities/Implementations/EnemyEntity.h"
#include "PaperTileMap.h"
#include "RoomInstance.generated.h"

class URoomTemplate;

USTRUCT(Blueprintable, BlueprintType)
struct DUNGEONSYSTEM_API FRoomInstance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	bool bIsCleared = false;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	FVector2D Position;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	UPaperTileMap* TileMap;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<AEnemyEntity*> Entities;
	
	FRoomInstance(bool bCond, UPaperTileMap* TileMap, FVector2D Position) :
	bIsCleared(bCond), Position(Position), TileMap(TileMap)
	{
		Entities.Empty();
	}

	FRoomInstance() {}
};
