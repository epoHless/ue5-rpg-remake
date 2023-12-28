#pragma once

#include "CoreMinimal.h"
#include "Entities/Implementations/EnemyEntity.h"
#include "GameFramework/Actor.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "EntityManager.generated.h"

UCLASS()
class ENTITYSYSTEM_API AEntityManager : public AActor
{
	GENERATED_BODY()

public:
	AEntityManager();

	UFUNCTION(BlueprintPure, Category = "RPG|Dungeon")
	AEntity* Get();

protected:
	
	UFUNCTION()
	void ToggleEnemies(FRoomInstance& Room);

	UFUNCTION()
	void DisableEntity(AEntity* Entity);
	bool Predicate(const AEntity& Entity);

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon")
	int32 EntitiesToSpawn = 2;
	
	UPROPERTY(VisibleAnywhere, Category = "RPG|Dungeon")
	TArray<AEntity*> Entities;

	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon")
	TSubclassOf<AEntity> EntityClass;

	FRoomInstance CurrentRoom;
};
