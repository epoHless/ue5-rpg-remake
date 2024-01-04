#pragma once

#include "CoreMinimal.h"
#include "Entities/Entity.h"
#include "Entities/Interfaces/Interactable.h"
#include "InteractableEntity.generated.h"

class UInteractionData;

UCLASS()
class ENTITYSYSTEM_API AInteractableEntity : public AEntity, public IInteractable
{
public:
	virtual void OnInteract_Implementation(APlayerEntity* PlayerEntity) override;

private:
	GENERATED_BODY()

	UPROPERTY()
	bool bIsInteractable = true;

public:
	AInteractableEntity();

	UPROPERTY(EditAnywhere, Category = "RPG|Interaction")
	UInteractionData* InteractionData;

protected:
	virtual void BeginPlay() override;

public:
};
