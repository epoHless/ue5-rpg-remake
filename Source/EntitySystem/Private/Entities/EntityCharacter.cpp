#include "EntitySystem/Public/Entities/EntityCharacter.h"

AEntityCharacter::AEntityCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEntityCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEntityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}