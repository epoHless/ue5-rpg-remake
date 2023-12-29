#include "Inventory/InventorySlot.h"

#include "Inventory/Items/Item.h"

void UInventorySlot::AddItem(UItem* NewItem)
{
	if(!HasItem())
	{
		Item = NewItem;
		if(!Item->bIsStackable) Stacks = -1;
		else Stacks = 0;
	}
	else if(Stacks != -1 && HasItem())
	{
		Stacks++;
	}
}

void UInventorySlot::RemoveItem()
{
	if(HasItem() && Stacks > 0)
	{
		Stacks--;
		if(Stacks <= 0) Item = nullptr;
	}
	else if(HasItem() && Stacks == -1)
	{
		Item = nullptr;
	}
}
