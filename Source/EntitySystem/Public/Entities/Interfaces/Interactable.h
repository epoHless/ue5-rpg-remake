#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APlayerEntity;

UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ENTITYSYSTEM_API IInteractable
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void OnInteract(APlayerEntity* PlayerEntity);
};
