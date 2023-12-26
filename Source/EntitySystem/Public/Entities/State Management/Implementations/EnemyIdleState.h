#pragma once

#include "CoreMinimal.h"
#include "IdleState.h"
#include "EnemyIdleState.generated.h"

UCLASS()
class ENTITYSYSTEM_API UEnemyIdleState : public UIdleState
{
public:
	virtual void OnEnter_Implementation(AEntity* Entity) override;
	virtual void OnExit_Implementation(AEntity* Entity) override;
	virtual void OnUpdate_Implementation(AEntity* Entity) override;

private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ToMovementRange = 100;

	UPROPERTY()
	APawn* PlayerPawn = nullptr;
};
