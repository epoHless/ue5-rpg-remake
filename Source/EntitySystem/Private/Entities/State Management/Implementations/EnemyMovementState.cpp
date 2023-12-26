#include "Entities/State Management/Implementations/EnemyMovementState.h"

#include "Entities/Entity.h"
#include "Entities/Implementations/EnemyEntity.h"
#include "GameFramework/PawnMovementComponent.h"

void UEnemyMovementState::OnEnter_Implementation(AEntity* Entity)
{
	if(PlayerPawn == nullptr) PlayerPawn = Cast<AEnemyEntity>(Entity)->GetPawn();
	Super::OnEnter_Implementation(Entity);
}

void UEnemyMovementState::OnExit_Implementation(AEntity* Entity)
{
	Super::OnExit_Implementation(Entity);
}

void UEnemyMovementState::OnUpdate_Implementation(AEntity* Entity)
{
	if (FVector::Distance(Entity->GetActorLocation(), PlayerPawn->GetActorLocation()) > PatrolRange)
	{
		Entity->ChangeState(Entity->EntityDataAsset->IdleState);
	}
	else
	{
		FVector Direction = PlayerPawn->GetActorLocation() - Entity->GetActorLocation();
		Entity->GetMovementComponent()->Velocity = Direction * MovementSpeed;
		
		if (FVector::Distance(Entity->GetActorLocation(), PlayerPawn->GetActorLocation()) < AttackRange)
		{
			UE_LOG(LogTemp, Display, TEXT("Can Attack!"));
			Entity->ChangeState(Entity->EntityDataAsset->AttackState);
		}
	}
	
	Super::OnUpdate_Implementation(Entity);
}
