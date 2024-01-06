#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "RoomManagement/Data/RoomTemplate.h"
#include "DungeonGameMode.generated.h"

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
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdateRoom(const FRoomInstance& RoomInstance);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Dungeon System")
	int32 XSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG|Dungeon System")
	int32 YSize = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG|Dungeon System")
	UItem* StartingItem;
	
private:

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<URoomTemplate*> Templates;

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
};
