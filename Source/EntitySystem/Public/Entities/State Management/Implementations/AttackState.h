#pragma once

#include "CoreMinimal.h"
#include "Entities/State Management/BaseState.h"
#include "AttackState.generated.h"

UCLASS()
class ENTITYSYSTEM_API UAttackState : public UBaseState
{
public:
	virtual void OnEnter_Implementation(AEntity* Entity) override;
	virtual void OnExit_Implementation(AEntity* Entity) override;
	virtual void OnUpdate_Implementation(AEntity* Entity, AGameModeBase* GameMode) override;

private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	float Damage;
	
	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	float Range;

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	float AttackRate = 1;

	float CurrentTime;

	UPROPERTY()
	APawn* PlayerPawn;
};
