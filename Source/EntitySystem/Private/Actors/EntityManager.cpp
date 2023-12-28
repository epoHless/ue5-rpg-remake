#include "Actors/EntityManager.h"

#include "FunctionLibraries/ExtensionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/RoomSubsystem.h"

AEntityManager::AEntityManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

AEntity* AEntityManager::Get()
{
	for (const auto Entity : Entities)
	{
		if(!Entity->bEnabled) return Entity;
	}

	return nullptr;
}

void AEntityManager::BeginPlay()
{
	Super::BeginPlay();

	Entities.Empty();

	if(EntityClass != nullptr)
	{
		UWorld* const World = GetWorld();

		if (World != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
			for (int i = 0; i < EntitiesToSpawn; i++)
			{
				AEntity* Entity = World->SpawnActor<AEntity>(EntityClass, GetActorLocation(), GetActorRotation(), SpawnParams);
				Entity->OnDeath.AddDynamic(this, &AEntityManager::DisableEntity);
				Entity->Toggle(false);
		
				Entities.Add(Entity);
			}
	
			const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
			RoomSubsystem->OnRoomChanged.AddDynamic(this, &AEntityManager::ToggleEnemies);
		}
	}
}

void AEntityManager::ToggleEnemies(const FRoomInstance& Room)
{
	for (const auto Entity : Entities)
	{
		Entity->Toggle(false);
	}
	
	for (int i = 0; i < Room.Entities.Num(); ++i)
	{
		if(Room.Entities[i].Value) continue;
		
		const auto Entity = Get();
		
		if(Entity != nullptr)
		{
			Entity->SetupEntity(Room.Entities[i].Key);
			Entity->SetActorLocation(FVector(100 * (1 + i),100 * (1 + i), 15));
			Entity->Toggle(true);
		}
	}
}

void AEntityManager::DisableEntity(AEntity* Entity)
{
	Entity->Toggle(false);
	Entity->SetActorLocation(GetActorLocation());
}