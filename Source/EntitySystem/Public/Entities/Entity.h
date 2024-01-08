#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Data/EntityDataAsset.h"
#include "Data/FlipbookDataAsset.h"
#include "Interfaces/Damageable.h"

#include "Entity.generated.h"

class UStatusComponent;
class UEntityDataAsset;
class UBaseState;
class UPaperFlipbook;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthCallback, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathCallback, AEntity*, Entity);

UCLASS(Abstract, Blueprintable, BlueprintType)
class ENTITYSYSTEM_API AEntity : public APaperCharacter, public IDamageable
{
public:
	AEntity();
	
	UFUNCTION(BlueprintCallable)
	virtual void SetHealth_Implementation(float HP) override;

	UFUNCTION(BlueprintCallable)
	virtual void AddHP_Implementation(float HP) override;

	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage_Implementation(float Damage, UStatusEffect* Effect) override;

	FORCEINLINE virtual float GetHP() const override { return CurrentHealth; }

	UPROPERTY(BlueprintAssignable)
	FHealthCallback OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FHealthCallback OnDamageTaken;

	UPROPERTY(BlueprintAssignable)
	FDeathCallback OnDeath;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	UEntityDataAsset* EntityDataAsset;

	void SetFlipbook(UPaperFlipbook* Flipbook);

	FORCEINLINE UPaperFlipbook* GetIdleFlipbook() const { return EntityDataAsset->FlipbookDataAsset->IdleFlipbook; }
	FORCEINLINE UPaperFlipbook* GetRunFlipbook() const { return EntityDataAsset->FlipbookDataAsset->RunFlipbook; }

	void ChangeState(UBaseState* State);

	UFUNCTION(BlueprintCallable, Category = "RPG|Entity")
	void ToggleEntity(bool bValue);
	
	bool bEnabled;

	UFUNCTION(BlueprintCallable)
	void SetupEntity(UEntityDataAsset* Data);

	UFUNCTION(BlueprintPure)
	FORCEINLINE UStatusComponent* GetStatusComponent() const { return StatusComponent; }
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	void SetupComponents();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RPG|Entity|Status")
	UStatusComponent* StatusComponent;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity")
	UBaseState* CurrentState;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity|Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity|Health")
	float CurrentHealth;

private:
	GENERATED_BODY()
};