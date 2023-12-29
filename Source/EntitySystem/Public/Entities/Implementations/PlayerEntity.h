#pragma once

#include "CoreMinimal.h"
#include "Entities/Entity.h"
#include "PlayerEntity.generated.h"

UCLASS()
class ENTITYSYSTEM_API APlayerEntity : public AEntity
{
public:
	virtual void TakeDamage_Implementation(float Damage) override;

private:
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FHealthCallback OnShieldChanged;

	UPROPERTY()
	float MaxShield = 100;
	
	UPROPERTY()
	float CurrentShield;

public:
	APlayerEntity();

protected:
	virtual void BeginPlay() override;
};