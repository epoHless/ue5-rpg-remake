#pragma once

#include "CoreMinimal.h"
#include "Entities/State Management/BaseState.h"
#include "MovementState.generated.h"

UCLASS()
class ENTITYSYSTEM_API UMovementState : public UBaseState
{
public:
	virtual void OnEnter_Implementation(AEntity* Entity) override;
	virtual void OnExit_Implementation(AEntity* Entity) override;
	virtual void OnUpdate_Implementation(AEntity* Entity) override;

private:
	GENERATED_BODY()

};
