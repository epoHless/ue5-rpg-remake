#include "Entities/State Management/Implementations/AttackState.h"

#include "Entities/Entity.h"
#include "Entities/Implementations/EnemyEntity.h"

void UAttackState::OnEnter_Implementation(AEntity* Entity)
{
	if(PlayerPawn == nullptr) PlayerPawn = Cast<AEnemyEntity>(Entity)->GetPawn();
	Super::OnEnter_Implementation(Entity);
}

void UAttackState::OnExit_Implementation(AEntity* Entity)
{
	Super::OnExit_Implementation(Entity);
}

void UAttackState::OnUpdate_Implementation(AEntity* Entity)
{
	if (FVector::Distance(Entity->GetActorLocation(), PlayerPawn->GetActorLocation()) > Range)
	{
		UE_LOG(LogTemp, Display, TEXT("Can Attack!"));
		Entity->ChangeState(Entity->EntityDataAsset->MovementState);
	}
}
