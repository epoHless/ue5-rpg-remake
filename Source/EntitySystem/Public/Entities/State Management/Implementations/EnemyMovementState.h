#pragma once

#include "CoreMinimal.h"
#include "MovementState.h"
#include "EnemyMovementState.generated.h"

UCLASS()
class ENTITYSYSTEM_API UEnemyMovementState : public UMovementState
{
public:
	virtual void OnEnter_Implementation(AEntity* Entity) override;
	virtual void OnExit_Implementation(AEntity* Entity) override;
	virtual void OnUpdate_Implementation(AEntity* Entity, AGameModeBase* GameMode) override;

private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	float MovementSpeed = 50;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	float ToAttackDistance = 100;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	float ToIdleDistance = 200;

	UPROPERTY()
	APawn* PlayerPawn = nullptr;
};
