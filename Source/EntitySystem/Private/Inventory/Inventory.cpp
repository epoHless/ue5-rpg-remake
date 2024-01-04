#include "Inventory/Inventory.h"

#include "Entities/Implementations/PlayerEntity.h"
#include "Inventory/InventorySlot.h"
#include "Kismet/GameplayStatics.h"

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

UInventorySlot* UInventory::GetFirstFreeSlot(const UItem* Item) const
{
	for (const auto InventorySlot : InventorySlots)
	{
		if(Item->bIsStackable && InventorySlot->Item == Item || !InventorySlot->HasItem()) return InventorySlot;
	}

	return nullptr;
}

bool UInventory::AddItem(UItem* Item) const
{
	const auto Slot = GetFirstFreeSlot(Item);

	if(Slot != nullptr)
	{
		Slot->AddItem(Item);
		OnItemAdded.Broadcast(Slot, InventorySlots.IndexOfByKey(Slot));
		return true;
	}

	return false;
}

bool UInventory::RemoveItem(UInventorySlot* Slot) const
{
	if(Slot != nullptr)
	{
		if(Slot->Item->bIsInfinite) return false;
		
		Slot->RemoveItem();
		OnItemRemoved.Broadcast(Slot, InventorySlots.IndexOfByKey(Slot));
		return true;
	}

	return false;
}

void UInventory::UseItem()
{
	const auto Owner = Cast<APlayerEntity>(GetOwner());
	
	if(CurrentSlot->Item != nullptr)
	{
		CurrentSlot->Item->Execute(Owner, UGameplayStatics::GetGameMode(this));
		RemoveItem(CurrentSlot);
	}
}

void UInventory::ChangeSlot(int Value)
{
	auto Index = InventorySlots.IndexOfByKey(CurrentSlot);
	Index += Value;

	if (Index < 0)
	{
		Index = InventorySlots.Num() - 1;
	}
	else if (Index >= InventorySlots.Num())
	{
		Index = 0;
	}

	if(CurrentSlot->Item != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item name: %s"), *CurrentSlot->Item->Name);
	}

	CurrentSlot = InventorySlots[Index];
	OnSlotChanged.Broadcast(CurrentSlot, Index);
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
