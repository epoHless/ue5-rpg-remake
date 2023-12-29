#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemEffect.generated.h"

class AEntity;

UCLASS(Blueprintable, BlueprintType, Abstract)
class ENTITYSYSTEM_API UItemEffect : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Inventory|Items")
	void Execute(AEntity* User);
};
