#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Data/EntityDataAsset.h"
#include "Data/FlipbookDataAsset.h"
#include "Interfaces/Damageable.h"

#include "Entity.generated.h"

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
	
	virtual void TakeDamage_Implementation(float Damage) override;
	
	FORCEINLINE virtual void AddHP(float HP) override
	{
		CurrentHealth += HP;
		OnHealthChanged.Broadcast(CurrentHealth/EntityDataAsset->Health);

		if(CurrentHealth > EntityDataAsset->Health) CurrentHealth = EntityDataAsset->Health; 
	}

	FORCEINLINE virtual float GetHP() const override { return CurrentHealth; }

	UPROPERTY(BlueprintAssignable)
	FHealthCallback OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FDeathCallback OnDeath;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	UEntityDataAsset* EntityDataAsset;

	void SetFlipbook(UPaperFlipbook* Flipbook);

	FORCEINLINE UPaperFlipbook* GetIdleFlipbook() const { return EntityDataAsset->FlipbookDataAsset->IdleFlipbook; }
	FORCEINLINE UPaperFlipbook* GetRunFlipbook() const { return EntityDataAsset->FlipbookDataAsset->RunFlipbook; }

	void ChangeState(UBaseState* State);

	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Entity")
	void ToggleEntity(bool bValue);
	
	bool bEnabled;

	UFUNCTION(BlueprintCallable)
	void SetupEntity(UEntityDataAsset* Data);
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	void SetupComponents();

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity")
	UBaseState* CurrentState;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity|Health")
	float CurrentHealth;

private:
	GENERATED_BODY()
};