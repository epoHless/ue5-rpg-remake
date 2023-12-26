#include "Entities/State Management/Implementations/IdleState.h"

#include "Entities/Entity.h"
#include "GameFramework/PawnMovementComponent.h"

void UIdleState::OnEnter_Implementation(AEntity* Entity)
{
	Entity->SetFlipbook(Entity->GetIdleFlipbook());
}

void UIdleState::OnExit_Implementation(AEntity* Entity)
{
}

void UIdleState::OnUpdate_Implementation(AEntity* Entity)
{
	if (Entity->GetMovementComponent()->Velocity != FVector::ZeroVector)
	{
		Entity->ChangeState(Entity->EntityDataAsset->MovementState);	
	}	
}
