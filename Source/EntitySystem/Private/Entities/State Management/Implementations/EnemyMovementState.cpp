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

void UEnemyMovementState::OnUpdate_Implementation(AEntity* Entity, AGameModeBase* GameMode)
{
	if (FVector::Distance(Entity->GetActorLocation(), PlayerPawn->GetActorLocation()) <= ToIdleDistance)
	{
		FVector Direction = PlayerPawn->GetActorLocation() - Entity->GetActorLocation();
		Direction.Normalize();

		Entity->AddMovementInput(Direction * MovementSpeed);
		
		// const FVector NewLocation = Entity->GetActorLocation() + Direction * MovementSpeed;
		// Entity->SetActorLocation(NewLocation);
		
		if (FVector::Distance(Entity->GetActorLocation(), PlayerPawn->GetActorLocation()) < ToAttackDistance)
		{
			UE_LOG(LogTemp, Display, TEXT("Can Attack!"));
			Entity->ChangeState(Entity->EntityDataAsset->AttackState);
		}
	}
	else
	{
		Entity->ChangeState(Entity->EntityDataAsset->IdleState);
	}
}
