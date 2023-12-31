﻿#include "Entities/State Management/Implementations/AttackState.h"

#include "Entities/Entity.h"
#include "Entities/Implementations/EnemyEntity.h"
#include "Entities/Status System/StatusComponent.h"
#include "GameFramework/GameModeBase.h"

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

void UAttackState::Attack_Implementation(AEntity* Entity, AGameModeBase* GameMode)
{
	FVector TraceStart = Entity->GetActorLocation();
	FVector TraceDirection = (PlayerPawn->GetActorLocation() - TraceStart).GetSafeNormal();
	FVector TraceEnd = TraceStart + (TraceDirection * Range);

	FHitResult Result;

	if (GameMode->GetWorld()->LineTraceSingleByChannel(OUT Result, TraceStart + (TraceDirection * 10), TraceEnd, ECC_Camera))
	{
		if(Result.GetActor()->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
		{
			IDamageable::Execute_TakeDamage(Result.GetActor(), Damage, Effect.GetDefaultObject());

			Cast<ACharacter>(Result.GetActor())->LaunchCharacter(TraceDirection * 20, false, false);
			Entity->LaunchCharacter(TraceDirection * 20, false, false);
		}
	}
}
