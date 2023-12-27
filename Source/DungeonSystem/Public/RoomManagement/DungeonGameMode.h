#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "RoomManagement/Data/RoomTemplate.h"
#include "DungeonGameMode.generated.h"

class APaperTileMapActor;

UCLASS(Blueprintable, BlueprintType)
class DUNGEONSYSTEM_API ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADungeonGameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	TArray<URoomTemplate*> Templates;

	FRoomInstance Rooms[10][10];

	UPROPERTY(VisibleAnywhere, Category = "RPG|Dungeon System")
	FRoomInstance CurrentRoom;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	float TPLenght = 170;
	
	void InitDungeon();

	UFUNCTION()
	void ChangeRoom(FIntVector Direction);
};
