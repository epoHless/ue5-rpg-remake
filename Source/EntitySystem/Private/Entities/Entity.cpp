#include "EntitySystem/Public/Entities/Entity.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Entities/State Management/BaseState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AEntity::TakeDamage_Implementation(float Damage)
{
	CurrentHealth -= Damage;

	OnHealthChanged.Broadcast(CurrentHealth/EntityDataAsset->Health);
	UE_LOG(LogTemp, Display, TEXT("%s Entity with %f HPs"), *GetName(), CurrentHealth);
	
	if(CurrentHealth <= 0)
	{
		OnDeath_Implementation();
		OnDeath.Broadcast(this);
	}
}

void AEntity::SetupComponents()
{
	GetSprite()->SetRelativeRotation(FRotator(0,0,-90));

	GetCapsuleComponent()->SetCapsuleRadius(5);
	GetCapsuleComponent()->SetCapsuleHalfHeight(10);

	GetCharacterMovement()->GravityScale = 0;
}

AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupComponents();
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location = GetActorLocation();
	SetActorLocation(FVector(Location.X, Location.Y, 15));
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(CurrentState != nullptr) CurrentState->OnUpdate(this, UGameplayStatics::GetGameMode(this));
}

void AEntity::SetFlipbook(UPaperFlipbook* Flipbook)
{
	GetSprite()->SetFlipbook(Flipbook);
}

void AEntity::SetupEntity(UEntityDataAsset* Data)
{
	if(Data->FlipbookDataAsset != nullptr)
	{
		EntityDataAsset = Data;
		
		CurrentHealth = Data->Health;
		SetFlipbook(Data->FlipbookDataAsset->IdleFlipbook);
		ChangeState(Data->IdleState);
	}
	
	CurrentHealth = Data->Health;
	OnHealthChanged.Broadcast(1);

	CurrentState->OnEnter(this);
}

void AEntity::ChangeState(UBaseState* State)
{
	if(CurrentState != nullptr) CurrentState->OnExit(this);
	CurrentState = State;
	CurrentState->OnEnter(this);
}

void AEntity::ToggleEntity_Implementation(bool bValue)
{
	bEnabled = bValue;
	SetActorTickEnabled(bValue);
	SetActorHiddenInGame(!bValue);
	SetActorEnableCollision(bValue);
}
