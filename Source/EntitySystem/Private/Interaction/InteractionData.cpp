#include "Interaction/InteractionData.h"

#include "Entities/Implementations/PlayerEntity.h"
#include "Inventory/Items/Effects/ItemEffect.h"

void UInteractionData::Execute_Implementation(APlayerEntity* User, AGameModeBase* GameMode)
{
	Effect->Execute_Implementation(GameMode, User);
}
