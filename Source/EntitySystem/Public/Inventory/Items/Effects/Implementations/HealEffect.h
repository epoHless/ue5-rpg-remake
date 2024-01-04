#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/Effects/ItemEffect.h"
#include "HealEffect.generated.h"

UCLASS()
class ENTITYSYSTEM_API UHealEffect : public UItemEffect
{
public:
	virtual void Execute_Implementation(AGameModeBase* GameMode, APlayerEntity* User) override;

private:
	GENERATED_BODY()
};
