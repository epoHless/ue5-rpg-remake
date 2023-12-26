#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Data/FlipbookDataAsset.h"

#include "Entity.generated.h"

class UBaseState;
class UPaperFlipbook;

UCLASS(Abstract, Blueprintable, BlueprintType)
class ENTITYSYSTEM_API AEntity : public APaperCharacter
{
	GENERATED_BODY()

public:
	AEntity();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	UFlipbookDataAsset* FlipbookDataAsset;

	void SetupEntity();

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity")
	UBaseState* CurrentState;
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	TSubclassOf<UBaseState> IdleState;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	TSubclassOf<UBaseState> MovementState;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	TSubclassOf<UBaseState> AttackState;
	
	void SetFlipbook(UPaperFlipbook* Flipbook);

	FORCEINLINE UPaperFlipbook* GetIdleFlipbook() const { return FlipbookDataAsset->IdleFlipbook; } 
	FORCEINLINE UPaperFlipbook* GetRunFlipbook() const { return FlipbookDataAsset->RunFlipbook; }

	void ChangeState(TSubclassOf<UBaseState> State);
};
