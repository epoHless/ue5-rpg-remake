#include "RangedAttackState.h"

#include "Actors/Projectile.h"
#include "Entities/Entity.h"
#include "GameFramework/GameModeBase.h"

void URangedAttackState::Attack_Implementation(AEntity* Entity, AGameModeBase* GameMode)
{
	const FVector SpawnLocation = Entity->GetActorLocation();
	const FVector Direction = (PlayerPawn->GetActorLocation() - SpawnLocation).GetSafeNormal();

	const auto Projectile = GameMode->GetWorld()->SpawnActor<AProjectile>(SpawnLocation + (Direction * 20), Entity->GetActorRotation());
	Projectile->InitProjectile(Direction, ProjectileData);
}
