#pragma once

#include "CoreMinimal.h"
#include "Bound.h"
#include "GameFramework/Actor.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "RoomManagement/Data/RoomTemplate.h"
#include "DungeonManager.generated.h"

class URoomTemplate;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDungeonCallback, FRoomInstance, Room);

class APaperTileMapActor;

UCLASS(Blueprintable, BlueprintType)
class DUNGEONSYSTEM_API ADungeonManager : public AActor
{
	GENERATED_BODY()

public:
	ADungeonManager();

	UPROPERTY(BlueprintAssignable)
	FDungeonCallback OnRoomChanged;

private:

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<ABound*> Bounds;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<URoomTemplate*> Templates;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<FRoomInstance> Rooms;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	FRoomInstance CurrentRoom;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	APaperTileMapActor* TilemapActor;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	int32 XSize;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	int32 YSize;

	UFUNCTION()
	void OnOverlap(FVector2D Direction);
	
	void InitDungeon();
	void ChangeRoom(FVector2D Direction);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
