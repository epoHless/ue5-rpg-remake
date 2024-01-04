#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/FlipbookDataAsset.h"
#include "EntityDataAsset.generated.h"

enum class ETypeInfo : uint8;
class UBaseState;

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API UEntityDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	ETypeInfo Type;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity", meta = (UIMin = "0.0", UIMax = "1.0"))
	float ItemSpawnRate;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	float ExperienceToGive;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Entity|Health")
	float Health;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	UFlipbookDataAsset* FlipbookDataAsset;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Entity|States")
	UBaseState* IdleState;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity|States")
	UBaseState* MovementState;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity|States")
	UBaseState* AttackState;

	
};
