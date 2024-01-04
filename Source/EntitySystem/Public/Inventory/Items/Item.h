#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item.generated.h"

class UPaperSprite;
class APlayerEntity;
class UItemEffect;

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API UItem : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory")
	bool bIsInfinite = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory")
	bool bIsStackable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory")
	UPaperSprite* Sprite;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Inventory")
	TSubclassOf<UItemEffect> Effect;

	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Inventory")
	void Execute(APlayerEntity* User, AGameModeBase* GameMode);
};
