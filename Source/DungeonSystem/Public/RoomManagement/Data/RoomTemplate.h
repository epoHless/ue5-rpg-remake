#pragma once

#include "PaperTileMap.h"
#include "EntitySystem/Public/Data/EntityDataAsset.h"
#include "RoomTemplate.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DUNGEONSYSTEM_API URoomTemplate : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System", meta = (UIMin = "0.0", UIMax = "1.0"))
	float Probability;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	UPaperTileMap* TileMap;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<UEntityDataAsset*> SpawnableEntities;
};
