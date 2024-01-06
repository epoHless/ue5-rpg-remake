#pragma once

#include "CoreMinimal.h"
#include "Entities/State Management/Implementations/AttackState.h"
#include "RangedAttackState.generated.h"

class UProjectileData;

UCLASS()
class ENTITYSYSTEM_API URangedAttackState : public UAttackState
{
public:
	virtual void Attack_Implementation(AEntity* Entity, AGameModeBase* GameMode) override;

private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UProjectileData* ProjectileData;
};
