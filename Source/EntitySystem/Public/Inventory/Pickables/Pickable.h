#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pickable.generated.h"

class APlayerEntity;
class UItem;

UINTERFACE(Blueprintable, BlueprintType)
class UPickable : public UInterface
{
	GENERATED_BODY()
};

class ENTITYSYSTEM_API IPickable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnPickup(APlayerEntity* PlayerEntity);

	UFUNCTION(BlueprintNativeEvent)
	void OnSpawn(UItem* PlayerEntity);
};
