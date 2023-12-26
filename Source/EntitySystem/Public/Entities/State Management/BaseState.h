#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseState.generated.h"

class AEntity;

UCLASS(Abstract, Blueprintable, BlueprintType)
class ENTITYSYSTEM_API UBaseState : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Entities")
	void OnEnter(AEntity* Entity);

	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Entities")
	void OnUpdate(AEntity* Entity, AGameModeBase* GameMode);

	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Entities")
	void OnExit(AEntity* Entity);
};
