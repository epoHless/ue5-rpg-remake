#include "Inventory/Items/Item.h"
#include "EntitySystem/Public/Inventory/Items/Effects/ItemEffect.h"

void UItem::Execute_Implementation(APlayerEntity* User, AGameModeBase* GameMode)
{
	Effect.GetDefaultObject()->Execute(GameMode, User);
}
