﻿#pragma once

#include "CoreMinimal.h"
#include "EntityInstance.generated.h"

class UEntityDataAsset;

USTRUCT(BlueprintType)
struct ENTITYSYSTEM_API FEntityInstance
{
	GENERATED_USTRUCT_BODY()

	FEntityInstance(){}

	FEntityInstance(UEntityDataAsset* DataAsset, float CurrentHP, bool bActive) :
	Data(DataAsset), CurrentHP(CurrentHP), bActive(bActive){}

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	UEntityDataAsset* Data;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	float CurrentHP;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	bool bActive = true;
};
