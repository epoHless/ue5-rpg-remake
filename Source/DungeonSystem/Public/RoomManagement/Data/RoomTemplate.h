#pragma once

#include "PaperTileMap.h"
#include "SpawnInfo.h"
#include "RoomTemplate.generated.h"

UENUM(BlueprintType)
enum class ETypeInfo : uint8
{
	ENEMY = 0			UMETA(DisplayName = "Enemy"),
	INTERACTABLE = 1	UMETA(DisplayName = "Interactable"),
	BOSS = 2			UMETA(DisplayName = "Boss"),
};

UCLASS(Blueprintable, BlueprintType)
class DUNGEONSYSTEM_API URoomTemplate : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System", meta = (UIMin = "0.0", UIMax = "1.0"))
	float Probability;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	ETypeInfo Type;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	UPaperTileMap* TileMap;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<FSpawnInfo> SpawnableEntities;
};