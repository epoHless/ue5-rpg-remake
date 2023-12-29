#include "Entities/Implementations/PlayerEntity.h"

#include "Inventory/Inventory.h"

void APlayerEntity::TakeDamage_Implementation(float Damage)
{
	if(CurrentShield <= 0)
	{
		Super::TakeDamage_Implementation(Damage);
	}
	
	float LeftOverDamage = 0;
	
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
		
		OnHealthChanged.Broadcast(CurrentHealth/EntityDataAsset->Health);
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

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	const auto DataObjectFinder = ConstructorHelpers::FObjectFinder<UEntityDataAsset>(TEXT("/Script/EntitySystem.EntityDataAsset'/Game/Core/Data/Player/PlayerData.PlayerData'"));
	EntityDataAsset = DataObjectFinder.Object;

	SetupEntity(EntityDataAsset);
	SetupComponents();
}

void APlayerEntity::BeginPlay()
{
	Super::BeginPlay();

	CurrentShield = MaxShield;
}