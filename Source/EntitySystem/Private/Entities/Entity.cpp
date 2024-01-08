#include "EntitySystem/Public/Entities/Entity.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Entities/State Management/BaseState.h"
#include "Entities/Status System/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("Status Component"));
	StatusComponent->RegisterComponent();
	
	SetupComponents();
}

void AEntity::SetupComponents()
{
	GetSprite()->SetRelativeRotation(FRotator(0,0,-90));

	GetCapsuleComponent()->SetCapsuleRadius(5);
	GetCapsuleComponent()->SetCapsuleHalfHeight(10);

	GetCharacterMovement()->GravityScale = 0;
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location = GetActorLocation();
	SetActorLocation(FVector(Location.X, Location.Y, 15));
}

void AEntity::SetupEntity(UEntityDataAsset* Data)
{
	EntityDataAsset = Data;

	if(Data->FlipbookDataAsset != nullptr)
	{
		SetFlipbook(Data->FlipbookDataAsset->IdleFlipbook);
	}

	CurrentHealth = Data->Health;
	
	MaxHealth = Data->Health;
	OnHealthChanged.Broadcast(CurrentHealth/MaxHealth);

	ChangeState(Data->IdleState);
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

void AEntity::ChangeState(UBaseState* State)
{
	if(CurrentState != nullptr) CurrentState->OnExit(this);
	CurrentState = State;
	CurrentState->OnEnter(this);
}

void AEntity::ToggleEntity(bool bValue)
{
	bEnabled = bValue;
	SetActorTickEnabled(bValue);
	SetActorHiddenInGame(!bValue);
	SetActorEnableCollision(bValue);

	GetMovementComponent()->Velocity = FVector::ZeroVector;
}

void AEntity::TakeDamage_Implementation(float Damage, UStatusEffect* Effect)
{
	CurrentHealth -= Damage;

	OnHealthChanged.Broadcast(CurrentHealth/MaxHealth);
	
	UE_LOG(LogTemp, Warning, TEXT("%s Entity with %f HPs"), *GetName(), CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("Percentage %f HPs"), CurrentHealth/MaxHealth);

	if(Effect)
	{
		const float Rand = FMath::RandRange(0.0f, 1.0f);

		if (Rand <= Effect->Probability)
		{
			GetStatusComponent()->AddStatus(Effect);
		}
	}
	
	if(CurrentHealth <= 0)
	{
		OnDeath_Implementation();
		OnDeath.Broadcast(this);
	}
}

void AEntity::AddHP_Implementation(float HP)
{
	CurrentHealth += HP;
	OnHealthChanged.Broadcast(CurrentHealth/MaxHealth);

	if(CurrentHealth > MaxHealth) CurrentHealth = MaxHealth; 
}

void AEntity::SetHealth_Implementation(float HP)
{
	CurrentHealth = HP;
	OnHealthChanged.Broadcast(CurrentHealth/MaxHealth);
}