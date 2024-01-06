#pragma once

#include "CoreMinimal.h"
#include "PaperTileMap.h"
#include "RoomTemplate.h"
#include "Data/EntityDataAsset.h"
#include "Data/EntityInstance.h"
#include "RoomInstance.generated.h"

class URoomTemplate;

USTRUCT(Blueprintable, BlueprintType)
struct DUNGEONSYSTEM_API FRoomInstance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	ETypeInfo Type;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG|Dungeon System")
	FIntVector Position;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	UPaperTileMap* TileMap;

	UPROPERTY(VisibleAnywhere)
	TArray<FEntityInstance> Entities;
	
	FRoomInstance(const URoomTemplate* Template, FIntVector Position) :
	Position(Position), TileMap(Template->TileMap)
	{
		Type = Template->Type;
		
		for (int i = 0; i < 2; ++i)
		{
			const auto Data = Template->SpawnableEntities[i];
			Entities.Add(FEntityInstance(Data.Entity, Data.Entity->Health, Data.Position , true));
		}
	}

	bool IsCompleted()
	{
		for (int i = 0; i < Entities.Num(); ++i)
		{
			if(!Entities[i].bActive) return false;
		}
		
		return true;
	}

	FRoomInstance() {}
};
