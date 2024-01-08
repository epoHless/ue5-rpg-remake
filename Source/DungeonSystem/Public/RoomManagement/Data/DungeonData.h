#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RoomManagement/Data/RoomTemplate.h"
#include "DungeonData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DUNGEONSYSTEM_API UDungeonData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG|Dungeon System")
	int32 X;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG|Dungeon System")
	int32 Y;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<URoomTemplate*> Templates;
};
