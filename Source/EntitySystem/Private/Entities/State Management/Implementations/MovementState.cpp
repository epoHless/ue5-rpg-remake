#include "Entities/State Management/Implementations/MovementState.h"
#include "Entities/Entity.h"
#include "GameFramework/PawnMovementComponent.h"

void UMovementState::OnEnter_Implementation(AEntity* Entity)
{
	Entity->SetFlipbook(Entity->GetRunFlipbook());
}

void UMovementState::OnExit_Implementation(AEntity* Entity)
{
}

void UMovementState::OnUpdate_Implementation(AEntity* Entity, AGameModeBase* GameMode)
{
	if (Entity->GetMovementComponent()->Velocity == FVector::ZeroVector)
	{
		Entity->ChangeState(Entity->EntityDataAsset->IdleState);	
	}	
}
