#pragma once

#include "CoreMinimal.h"
#include "EntityDataAsset.h"
#include "PlayerDataAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API UPlayerDataAsset : public UEntityDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "RPG|Entity|Health")
	float Shield;
};
