#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Data/EntityDataAsset.h"
#include "Data/FlipbookDataAsset.h"

#include "Entity.generated.h"

class UEntityDataAsset;
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