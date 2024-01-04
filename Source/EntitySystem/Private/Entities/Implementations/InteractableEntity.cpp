#include "Entities/Implementations/InteractableEntity.h"

#include "Interaction/InteractionData.h"
#include "Kismet/GameplayStatics.h"

void AInteractableEntity::OnInteract_Implementation(APlayerEntity* PlayerEntity)
{
	if(!bIsInteractable) return;
	
	InteractionData->Execute_Implementation(PlayerEntity, UGameplayStatics::GetGameMode(this));
	bIsInteractable = false;
}

AInteractableEntity::AInteractableEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractableEntity::BeginPlay()
{
	Super::BeginPlay();
}

