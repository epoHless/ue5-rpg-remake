#include "Actors/EntityManager.h"

#include "FunctionLibraries/ExtensionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "RoomManagement/DungeonGameMode.h"
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

	if(EntityClass != nullptr)
	{
		const UWorld* const World = GetWorld();

		if (World != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
			for (const auto Entity : Entities)
			{
				Entity->OnDeath.AddDynamic(this, &AEntityManager::DisableEntity);
				Entity->ToggleEntity(false);
		
				Entities.Add(Entity);
			}
	
			const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
			RoomSubsystem->OnRoomChanged.AddDynamic(this, &AEntityManager::ToggleEnemies);
		}
	}
}

void AEntityManager::ToggleEnemies(FRoomInstance& Room)
{
	for (int i = 0; i < CurrentRoom.Entities.Num(); ++i)
	{
		CurrentRoom.Entities[i].CurrentHP = Entities[i]->GetHP();
		Entities[i]->ToggleEntity(false);
	}

	Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this))->UpdateRoom(CurrentRoom);
	
	CurrentRoom = Room;
	
	for (int i = 0; i < CurrentRoom.Entities.Num(); ++i)
	{
		if(!CurrentRoom.Entities[i].bActive || CurrentRoom.Entities[i].CurrentHP <= 0) continue;
		
		const auto Entity = Get();
		
		if(Entity != nullptr)
		{
			Entity->SetupEntity(CurrentRoom.Entities[i].Data);
			Entity->SetHP(CurrentRoom.Entities[i].CurrentHP);
			Entity->SetActorLocation(FVector(100 * (1 + i),100, 15));
			Entity->ToggleEntity(true);

			UE_LOG(LogTemp, Display, TEXT("Loaded Entity with %f HPs"), Entity->GetHP());
		}
	}
}

void AEntityManager::DisableEntity(AEntity* Entity)
{
	const auto Instance = CurrentRoom.Entities.FindByPredicate([&Entity](const FEntityInstance& Element)
	{
		return Entity->EntityDataAsset == Element.Data;
	});
	
	Instance->bActive = false;
	Instance->CurrentHP = 0;
	
	Entity->ToggleEntity(false);
	Entity->SetActorLocation(GetActorLocation());
}