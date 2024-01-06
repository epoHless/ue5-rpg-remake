#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileData.generated.h"

class UPaperSprite;

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API UProjectileData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Misc")
	UPaperSprite* Sprite;
};
