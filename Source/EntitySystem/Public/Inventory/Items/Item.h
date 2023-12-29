#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item.generated.h"

class AEntity;
class UItemEffect;

UCLASS(Blueprintable, BlueprintType, Abstract)
class ENTITYSYSTEM_API UItem : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory|Items")
	bool bIsStackable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory|Items")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory|Items")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory|Items")
	TArray<TSubclassOf<UItemEffect>> Effects;

	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Inventory|Items")
	void Execute(AEntity* User);
};
