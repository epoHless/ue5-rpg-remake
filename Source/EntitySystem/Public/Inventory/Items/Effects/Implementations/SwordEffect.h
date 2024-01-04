#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/Effects/ItemEffect.h"
#include "SwordEffect.generated.h"

UCLASS()
class ENTITYSYSTEM_API USwordEffect : public UItemEffect
{
public:
	virtual void Execute_Implementation(AGameModeBase* GameMode, APlayerEntity* User) override;

private:
	GENERATED_BODY()
};
