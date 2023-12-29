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

	UFUNCTION()
	void InitSystem(FRoomInstance& Room);

protected:
	
	UFUNCTION()
	void ToggleEnemies(FRoomInstance& Room);

	UFUNCTION()
	void DisableEntity(AEntity* Entity);

	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon")
	TArray<AEntity*> Entities;

	UPROPERTY()
	FRoomInstance CurrentRoom;
};
