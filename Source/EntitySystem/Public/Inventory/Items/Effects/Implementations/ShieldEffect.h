#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/Effects/ItemEffect.h"
#include "ShieldEffect.generated.h"

UCLASS()
class ENTITYSYSTEM_API UShieldEffect : public UItemEffect
{
public:
	virtual void Execute_Implementation(AGameModeBase* GameMode, APlayerEntity* User) override;

private:
	GENERATED_BODY()
};
