#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/Item.h"
#include "Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryCallback, UInventorySlot*, Item);

class UInventorySlot;

UCLASS()
class ENTITYSYSTEM_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "RPG|Inventory|Items")
	FInventoryCallback OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "RPG|Inventory|Items")
	FInventoryCallback OnItemRemoved;
	
	UInventory();

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory|Items")
	bool HasFreeSlot() const;

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory|Items")
	UInventorySlot* GetFirstFreeSlot() const;

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory|Items")
	bool AddItem(UItem* Item) const;

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory|Items")
	bool RemoveItem(UInventorySlot* Item) const;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "RPG|Inventory|Items")
	int32 InventorySize = 6;
	
	UPROPERTY(VisibleAnywhere, Category = "RPG|Inventory|Items")
	TArray<UInventorySlot*> InventorySlots;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Inventory|Items")
	UInventorySlot* CurrentSlot;
};
