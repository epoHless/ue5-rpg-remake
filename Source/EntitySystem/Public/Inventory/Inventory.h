#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/Item.h"
#include "Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryCallback, UInventorySlot*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryUICallback, UInventorySlot*, Slot, int32, Index);

class UInventorySlot;

UCLASS()
class ENTITYSYSTEM_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "RPG|Inventory")
	FInventoryUICallback OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "RPG|Inventory")
	FInventoryUICallback OnItemRemoved;
	
	UPROPERTY(BlueprintAssignable, Category = "RPG|Inventory")
	FInventoryUICallback OnSlotChanged;
	
	UInventory();

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory")
	bool HasFreeSlot() const;

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory")
	UInventorySlot* GetFirstFreeSlot(const UItem* Item) const;

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory")
	bool AddItem(UItem* Item) const;

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory")
	bool RemoveItem(UInventorySlot* Item) const;

	UFUNCTION(BlueprintCallable, Category = "RPG|Inventory")
	void UseItem();

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory")
	UItem* GetCurrentItem();
	
	void ChangeSlot(int Value);

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	int32 InventorySize = 5;
	
	UPROPERTY()
	TArray<UInventorySlot*> InventorySlots;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Inventory|Items")
	UInventorySlot* CurrentSlot;
};
