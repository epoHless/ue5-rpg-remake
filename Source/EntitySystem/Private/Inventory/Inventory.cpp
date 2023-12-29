#include "Inventory/Inventory.h"
#include "Inventory/InventorySlot.h"

UInventory::UInventory()
{
}

bool UInventory::HasFreeSlot() const
{
	for (const auto InventorySlot : InventorySlots)
	{
		if(!InventorySlot->HasItem()) return true;
	}

	return false;
}

UInventorySlot* UInventory::GetFirstFreeSlot() const
{
	for (const auto InventorySlot : InventorySlots)
	{
		if(!InventorySlot->HasItem()) return InventorySlot;
	}

	return nullptr;
}

bool UInventory::AddItem(UItem* Item) const
{
	const auto Slot = GetFirstFreeSlot();

	if(Slot != nullptr)
	{
		Slot->AddItem(Item);
		OnItemAdded.Broadcast(Slot);
		return true;
	}

	return false;
}

bool UInventory::RemoveItem(UInventorySlot* Slot) const
{
	if(Slot != nullptr)
	{
		Slot->RemoveItem();
		OnItemRemoved.Broadcast(Slot);
		return true;
	}

	return false;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < InventorySize; ++i)
	{
		InventorySlots.Add(NewObject<UInventorySlot>());
	}

	CurrentSlot = InventorySlots[0];
}
