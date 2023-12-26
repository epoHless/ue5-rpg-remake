#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

UINTERFACE()
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class ENTITYSYSTEM_API IDamageable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintNativeEvent)
	void OnDeath();
};
