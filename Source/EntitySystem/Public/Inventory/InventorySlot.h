﻿#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventorySlot.generated.h"

class UItem;

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API UInventorySlot : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory|Items")
	UItem* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory|Items")
	int32 Stacks;
	
	UFUNCTION(BlueprintCallable, Category = "RPG|Inventory|Items")
	void AddItem(UItem* NewItem);

	UFUNCTION(BlueprintCallable, Category = "RPG|Inventory|Items")
	void RemoveItem();

	UFUNCTION(BlueprintPure, Category = "RPG|Inventory|Items")
	FORCEINLINE bool HasItem() const { return Item != nullptr; }
};
