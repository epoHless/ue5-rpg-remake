#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SpawnInfo.generated.h"

class UEntityDataAsset;

USTRUCT(Blueprintable, BlueprintType)
struct DUNGEONSYSTEM_API FSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	FSpawnInfo() {}

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	UEntityDataAsset* Entity;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	FVector Position;
};
