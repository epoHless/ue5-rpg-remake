#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InteractionData.generated.h"

class AEntity;
class UItemEffect;

UCLASS()
class ENTITYSYSTEM_API UInteractionData : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "RPG|Interaction")
	UItemEffect* Effect;
	
public:

	UFUNCTION(BlueprintNativeEvent, Category = "RPG|Interaction")
	void Execute(APlayerEntity* User, AGameModeBase* GameMode);
};
