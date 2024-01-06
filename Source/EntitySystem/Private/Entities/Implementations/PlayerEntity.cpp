#include "Entities/Implementations/PlayerEntity.h"

#include "Components/CapsuleComponent.h"
#include "Experience/ExperienceComponent.h"
#include "FunctionLibraries/ExtensionLibrary.h"
#include "Inventory/Inventory.h"
#include "Inventory/Pickables/Pickable.h"
#include "Kismet/GameplayStatics.h"
#include "Entities/Status System/StatusComponent.h"
#include "RoomManagement/DungeonGameMode.h"

void APlayerEntity::TakeDamage_Implementation(float Damage, UStatusEffect* Effect)
{
	if(CurrentShield <= 0)
	{
		Super::TakeDamage_Implementation(Damage, Effect);
	}
	
	float LeftOverDamage = 0;

	if(Effect)
	{
		const float Rand = FMath::RandRange(0.0f, 1.0f);

		if (Rand <= Effect->Probability)
		{
			GetStatusComponent()->AddStatus(Effect);
		}
	}
	
	if(CurrentShield > 0)
	{
		CurrentShield -= Damage;
		OnShieldChanged.Broadcast(CurrentShield/MaxShield);
	}

	if(CurrentShield < 0)
	{
		LeftOverDamage = FMath::Abs(CurrentShield);
		CurrentShield = 0;

		CurrentHealth -= LeftOverDamage;
		
		OnHealthChanged.Broadcast(CurrentHealth/MaxHealth);
		UE_LOG(LogTemp, Display, TEXT("%s Entity with %f HPs"), *GetName(), CurrentHealth);
	
		if(CurrentHealth <= 0)
		{
			OnDeath_Implementation();

			OnDeath.Broadcast(this);
		}
	}
}

void APlayerEntity::AddShield(float Value)
{
	CurrentShield += Value;
	OnShieldChanged.Broadcast(CurrentShield/MaxShield);

	if(CurrentShield > MaxShield) CurrentShield = MaxShield;
}

APlayerEntity::APlayerEntity()
{	
	PrimaryActorTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory Component"));
	Inventory->RegisterComponent();

	ExperienceComponent = CreateDefaultSubobject<UExperienceComponent>(TEXT("Experience Component"));
	ExperienceComponent->RegisterComponent();

	const auto DataObjectFinder = ConstructorHelpers::FObjectFinder<UEntityDataAsset>(TEXT("/Script/EntitySystem.EntityDataAsset'/Game/Core/Data/Player/PlayerData.PlayerData'"));
	EntityDataAsset = DataObjectFinder.Object;

	SetupEntity(EntityDataAsset);
	SetupComponents();
}


void APlayerEntity::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UPickable::StaticClass()))
	{
		IPickable::Execute_OnPickup(OtherActor, this);
	}
}

void APlayerEntity::OnLevelUp(float Quantity)
{
	MaxHealth *= Quantity;
	OnHealthChanged.Broadcast(CurrentHealth/MaxHealth);
}

void APlayerEntity::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerEntity::OnPickupOverlap);
	
	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
	RoomSubsystem->OnLevelUp.AddDynamic(this, &APlayerEntity::OnLevelUp);

	CurrentShield = MaxShield;
}
