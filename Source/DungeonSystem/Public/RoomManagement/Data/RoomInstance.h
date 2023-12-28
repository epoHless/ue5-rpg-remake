#pragma once

#include "CoreMinimal.h"
#include "PaperTileMap.h"
#include "RoomTemplate.h"
#include "Data/EntityInstance.h"
#include "RoomInstance.generated.h"

class URoomTemplate;

USTRUCT(Blueprintable, BlueprintType)
struct DUNGEONSYSTEM_API FRoomInstance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	FIntVector Position;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	UPaperTileMap* TileMap;

	UPROPERTY(VisibleAnywhere)
	TArray<FEntityInstance> Entities;
	
	FRoomInstance(const URoomTemplate* Template, FIntVector Position) :
	Position(Position), TileMap(Template->TileMap)
	{
		for (int i = 0; i < 2; ++i)
		{
			const auto Data = Template->SpawnableEntities[FMath::RandRange(0, Template->SpawnableEntities.Num() - 1)];
			Entities.Add(FEntityInstance(Data, Data->Health, true));
		}
	}

	bool IsCompleted()
	{
		return Entities[0].bActive && Entities[1].bActive;
	}

	FRoomInstance() {}
};
