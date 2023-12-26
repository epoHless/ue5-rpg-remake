#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/FlipbookDataAsset.h"
#include "EntityDataAsset.generated.h"

class UBaseState;

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API UEntityDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	UFlipbookDataAsset* FlipbookDataAsset;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Entity|States")
	UBaseState* IdleState;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity|States")
	UBaseState* MovementState;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity|States")
	UBaseState* AttackState;
};
