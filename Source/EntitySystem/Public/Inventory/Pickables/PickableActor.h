#pragma once

#include "CoreMinimal.h"
#include "Pickable.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteActor.h"
#include "PickableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickableCallback, APickableActor*, Pickable);

class UItem;

UCLASS()
class ENTITYSYSTEM_API APickableActor : public AActor, public IPickable
{
public:

	UPROPERTY(BlueprintAssignable)
	FPickableCallback OnItemPicked;
	
	virtual void OnPickup_Implementation(APlayerEntity* PlayerEntity) override;

private:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent;

public:
	APickableActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Items")
	UItem* Item;
	
	void SetupItem();

protected:
	virtual void BeginPlay() override;
};
