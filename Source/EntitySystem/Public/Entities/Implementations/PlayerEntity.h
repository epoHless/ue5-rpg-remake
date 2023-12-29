#pragma once

#include "CoreMinimal.h"
#include "Entities/Entity.h"
#include "PlayerEntity.generated.h"

class UInventory;

UCLASS()
class ENTITYSYSTEM_API APlayerEntity : public AEntity
{
public:
	virtual void TakeDamage_Implementation(float Damage) override;

private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Blueprintable, Category = "RPG|Inventory|Items")
	UInventory* Inventory;

	UPROPERTY(BlueprintAssignable)
	FHealthCallback OnShieldChanged;

	UPROPERTY()
	float MaxShield = 100;
	
	UPROPERTY()
	float CurrentShield;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetShield() { return CurrentShield; }

	UFUNCTION(BlueprintCallable)
	void AddShield(float Value);

public:
	APlayerEntity();

protected:
	virtual void BeginPlay() override;
};