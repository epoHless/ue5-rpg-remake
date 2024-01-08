#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "DungeonGameMode.generated.h"

class UDungeonData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameOverCallback, bool, Result);

class APaperTileMapActor;
class UItem;

UCLASS(Blueprintable, BlueprintType)
class DUNGEONSYSTEM_API ADungeonGameMode : public AGameModeBase
{

	GENERATED_BODY()

public:
	ADungeonGameMode();

protected:	
	virtual void BeginPlay() override;

	void Cleanup();

public:

	UPROPERTY(BlueprintAssignable)
	FGameOverCallback OnGameOver;

	UFUNCTION()
	void UpdateRoom(const FRoomInstance& RoomInstance);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG|Dungeon System")
	UItem* StartingItem;

	UFUNCTION(BlueprintCallable, Category = "RPG|Dungeon System")
	void SetDungeonData(UDungeonData* Data);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG|Dungeon System")
	UDungeonData* DungeonData;

	UFUNCTION(BlueprintPure, Category = "RPG|Dungeon System")
	FORCEINLINE FRoomInstance& GetCurrentRoom() { return CurrentRoom; }
	
private:
	void CalculateTotalWeight(float TotalSum, float& Random);
	URoomTemplate* ChoseRoom();

	FRoomInstance** Rooms;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Dungeon System")
	FRoomInstance CurrentRoom;
	
	UPROPERTY()
	float TPLenght = 170;

	void InitDungeon();

	UFUNCTION(BlueprintCallable, Category = "RPG|Dungeon System")
	void StartGame();
	
	UFUNCTION()
	void ChangeRoom(FIntVector Direction);

	UFUNCTION()
	void IsGameOver(FRoomInstance Room);

	int32 RoomsToClear;
	int32 ClearedRooms = 0;
};
