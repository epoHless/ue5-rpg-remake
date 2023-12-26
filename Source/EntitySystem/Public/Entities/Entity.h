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

UCLASS(Abstract, Blueprintable, BlueprintType)
class ENTITYSYSTEM_API AEntity : public APaperCharacter, public IDamageable
{
public:
	virtual void TakeDamage_Implementation(float Damage) override;

	UPROPERTY(BlueprintAssignable)
	FHealthCallback OnDamageTaken;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Entity|Health")
	float CurrentHealth;

private:
	GENERATED_BODY()

public:
	AEntity();

protected:
	virtual void BeginPlay() override;

	void SetupEntity();

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity")
	UBaseState* CurrentState;
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	UEntityDataAsset* EntityDataAsset;
	
	void SetFlipbook(UPaperFlipbook* Flipbook);

	FORCEINLINE UPaperFlipbook* GetIdleFlipbook() const { return EntityDataAsset->FlipbookDataAsset->IdleFlipbook; } 
	FORCEINLINE UPaperFlipbook* GetRunFlipbook() const { return EntityDataAsset->FlipbookDataAsset->RunFlipbook; }

	void ChangeState(UBaseState* State);
};