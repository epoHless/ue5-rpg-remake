#include "EntitySystem/Public/Entities/Entity.h"

AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}