#include "Inventory/Items/Item.h"
#include "EntitySystem/Public/Inventory/Items/Effects/ItemEffect.h"

void UItem::Execute_Implementation(AEntity* User)
{
	for (auto Effect : Effects)
	{
		Effect.GetDefaultObject()->Execute(User);
	}
}
