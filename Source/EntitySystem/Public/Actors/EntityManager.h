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

protected:
	
	UFUNCTION()
	void ToggleEnemies(const FRoomInstance& Room);
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TArray<AEntity*> Entities;
};
