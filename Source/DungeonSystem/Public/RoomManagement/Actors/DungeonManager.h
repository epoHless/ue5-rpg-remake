#pragma once

#include "CoreMinimal.h"
#include "Bound.h"
#include "GameFramework/Actor.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "DungeonManager.generated.h"

class APaperTileMapActor;

UCLASS(Blueprintable, BlueprintType)
class DUNGEONSYSTEM_API ADungeonManager : public AActor
{
	GENERATED_BODY()

public:
	ADungeonManager();

private:
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	APaperTileMapActor* TilemapActor;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<ABound*> Bounds;

protected:
	UFUNCTION()
	void ChangeTileset(const FRoomInstance& Room);
	
	virtual void BeginPlay() override;
};
