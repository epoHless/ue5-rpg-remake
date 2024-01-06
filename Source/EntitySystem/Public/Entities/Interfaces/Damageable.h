#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

class UStatusEffect;

UINTERFACE()
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class ENTITYSYSTEM_API IDamageable
{
	GENERATED_BODY()

public:

	virtual float GetHP() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void AddHP(float HP);
	
	UFUNCTION(BlueprintNativeEvent)
	void TakeDamage(float Damage, UStatusEffect* Effect);

	UFUNCTION(BlueprintNativeEvent)
	void OnDeath();

	UFUNCTION(BlueprintNativeEvent)
	void SetHealth(float HP);
};
