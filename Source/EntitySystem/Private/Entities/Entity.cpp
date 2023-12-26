#include "EntitySystem/Public/Entities/Entity.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Entities/State Management/BaseState.h"
#include "GameFramework/CharacterMovementComponent.h"

AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
	SetupEntity();
	
	CurrentState->OnEnter(this);
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentState->OnUpdate(this);
}

void AEntity::SetFlipbook(UPaperFlipbook* Flipbook)
{
	GetSprite()->SetFlipbook(Flipbook);
}

void AEntity::SetupEntity()
{
	if(EntityDataAsset->FlipbookDataAsset != nullptr)
	{
		SetFlipbook(EntityDataAsset->FlipbookDataAsset->IdleFlipbook);
		ChangeState(EntityDataAsset->IdleState);
	}

	GetSprite()->SetRelativeRotation(FRotator(0,0,-90));

	GetCapsuleComponent()->SetCapsuleRadius(5);
	GetCapsuleComponent()->SetCapsuleHalfHeight(10);

	GetCharacterMovement()->GravityScale = 0;
}

void AEntity::ChangeState(UBaseState* State)
{
	if(CurrentState != nullptr) CurrentState->OnExit(this);
	CurrentState = State;
	CurrentState->OnEnter(this);
}
