#pragma once

#include "CoreMinimal.h"
#include "Entities/Implementations/EnemyEntity.h"
#include "GameFramework/Actor.h"
#include "Inventory/Items/Item.h"
#include "Inventory/Pickables/PickableActor.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "EntityManager.generated.h"

UCLASS()
class ENTITYSYSTEM_API AEntityManager : public AActor
{
	GENERATED_BODY()

public:
	AEntityManager();

	UFUNCTION(BlueprintPure, Category = "RPG|Dungeon")
	AEntity* Get(ETypeInfo Type);

	UFUNCTION()
	void InitSystem(FRoomInstance Room);

protected:
	
	UFUNCTION()
	void ToggleEnemies(FRoomInstance Room);

	UFUNCTION()
	void DestroyItem(APickableActor* Pickable);
	void SpawnItem(const AEntity* Entity);
	UFUNCTION()
	void DisableEntity(AEntity* Entity);

	virtual void BeginPlay() override;
	void ResetItems();
	void SaveCurrentRoomData();
	void ToggleNewRoom(FRoomInstance Room);

private:

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon")
	TArray<UItem*> SpawnableItems;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon")
	TArray<APickableActor*> SpawnedItems;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon")
	TArray<AEntity*> Entities;

	UPROPERTY()
	FRoomInstance CurrentRoom;
};
