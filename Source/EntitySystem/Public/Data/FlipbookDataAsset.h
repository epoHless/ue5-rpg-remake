#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperFlipbook.h"
#include "FlipbookDataAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API UFlipbookDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "RPG|Entities")
	UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, Category = "RPG|Entities")
	UPaperFlipbook* RunFlipbook;
};
