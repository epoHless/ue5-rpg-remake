#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemEffect.generated.h"

class APlayerEntity;

UCLASS(Blueprintable, BlueprintType, Abstract)
class ENTITYSYSTEM_API UItemEffect : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Inventory")
	void Execute(AGameModeBase* GameMode, APlayerEntity* User);
};
