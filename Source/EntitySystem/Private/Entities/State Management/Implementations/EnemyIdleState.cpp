#include "Entities/State Management/Implementations/EnemyIdleState.h"

#include "Entities/Entity.h"
#include "Entities/Implementations/EnemyEntity.h"

void UEnemyIdleState::OnEnter_Implementation(AEntity* Entity)
{
	if(PlayerPawn == nullptr) PlayerPawn = Cast<AEnemyEntity>(Entity)->GetPawn();
	Super::OnEnter_Implementation(Entity);
}

void UEnemyIdleState::OnExit_Implementation(AEntity* Entity)
{
	Super::OnExit_Implementation(Entity);
}

void UEnemyIdleState::OnUpdate_Implementation(AEntity* Entity)
{
	if (FVector::Distance(Entity->GetActorLocation(), PlayerPawn->GetActorLocation()) < ToMovementRange)
	{
		Entity->ChangeState(Entity->EntityDataAsset->MovementState);
	}
}
