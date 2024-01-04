#pragma once

#include "CoreMinimal.h"
#include "Entities/Entity.h"
#include "PlayerEntity.generated.h"

class UExperienceComponent;
class UInventory;

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

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory|Items")
	FORCEINLINE UInventory* GetInventory() const { return Inventory; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetShield() { return CurrentShield; }

	UFUNCTION(BlueprintCallable)
	void AddShield(float Value);

protected:

	UPROPERTY(VisibleAnywhere, Blueprintable, Category = "RPG|Inventory|Items")
	UInventory* Inventory;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity|Experience")
	UExperienceComponent* ExperienceComponent;

	UFUNCTION()
	void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLevelUp(float Quantity);
	
	UFUNCTION()
	virtual void BeginPlay() override;
};