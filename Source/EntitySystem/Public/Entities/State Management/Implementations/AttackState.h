﻿#pragma once

#include "CoreMinimal.h"
#include "Entities/State Management/BaseState.h"
#include "AttackState.generated.h"

class UStatusEffect;

UCLASS()
class ENTITYSYSTEM_API UAttackState : public UBaseState
{
public:
	virtual void OnEnter_Implementation(AEntity* Entity) override;
	virtual void OnExit_Implementation(AEntity* Entity) override;
	virtual void OnUpdate_Implementation(AEntity* Entity, AGameModeBase* GameMode) override;

	UFUNCTION(BlueprintNativeEvent)
	void Attack(AEntity* Entity, AGameModeBase* GameMode);

protected:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "RPG|Entity")
	TSubclassOf<UStatusEffect> Effect;

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
