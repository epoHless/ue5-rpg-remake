#include "Entities/State Management/Implementations/AttackState.h"

#include "Entities/Entity.h"
#include "Entities/Implementations/EnemyEntity.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PawnMovementComponent.h"

void UAttackState::OnEnter_Implementation(AEntity* Entity)
{
	if(PlayerPawn == nullptr) PlayerPawn = Cast<AEnemyEntity>(Entity)->GetPawn();
	Super::OnEnter_Implementation(Entity);
}

void UAttackState::OnExit_Implementation(AEntity* Entity)
{
	Super::OnExit_Implementation(Entity);
}

void UAttackState::OnUpdate_Implementation(AEntity* Entity, AGameModeBase* GameMode)
{
	if (FVector::Distance(Entity->GetActorLocation(), PlayerPawn->GetActorLocation()) > Range)
	{
		Entity->ChangeState(Entity->EntityDataAsset->MovementState);
	}else
	{
		CurrentTime += GameMode->GetWorld()->DeltaTimeSeconds;
		
		if(CurrentTime >= AttackRate)
		{
			Attack(Entity, GameMode);
			CurrentTime = 0;
		}
	}
}

void UAttackState::Attack(AEntity* Entity, AGameModeBase* GameMode)
{
	FVector TraceStart = Entity->GetActorLocation();
	FVector TraceDirection = (PlayerPawn->GetActorLocation() - TraceStart).GetSafeNormal();
	FVector TraceEnd = TraceStart + (TraceDirection * Range);

	FHitResult Result;

	if (GameMode->GetWorld()->LineTraceSingleByChannel(OUT Result, TraceStart + (TraceDirection * 10), TraceEnd, ECC_Camera))
	{
		if(Result.GetActor()->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
		{
			IDamageable::Execute_TakeDamage(Result.GetActor(), Damage);
			UE_LOG(LogTemp, Display, TEXT("Attacking!"));
		}
	}
}