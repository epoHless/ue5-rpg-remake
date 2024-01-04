#include "Actors/EntityManager.h"

#include "FunctionLibraries/ExtensionLibrary.h"
#include "Inventory/Pickables/PickableActor.h"
#include "Kismet/GameplayStatics.h"
#include "RoomManagement/DungeonGameMode.h"
#include "Subsystems/RoomSubsystem.h"

AEntityManager::AEntityManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

AEntity* AEntityManager::Get(ETypeInfo Type)
{
	for (const auto Entity : Entities)
	{
		if(!Entity->bEnabled && Entity->EntityDataAsset->Type == Type) return Entity;
	}

	return nullptr;
}

void AEntityManager::InitSystem(FRoomInstance Room)
{
	const UWorld* const World = GetWorld();

	if (World != nullptr)
	{
		for (const auto Entity : Entities)
		{
			Entity->OnDeath.AddDynamic(this, &AEntityManager::DisableEntity);
			Entity->ToggleEntity(false);
		}

		const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
		RoomSubsystem->OnRoomChanged.AddDynamic(this, &AEntityManager::ToggleEnemies);
	}
}

void AEntityManager::BeginPlay()
{
	Super::BeginPlay();
	
	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
	RoomSubsystem->OnDungeonInit.AddDynamic(this, &AEntityManager::InitSystem);
}

void AEntityManager::ToggleEnemies(FRoomInstance Room)
{
	for (int i = 0; i < SpawnedItems.Num(); ++i)
	{
		SpawnedItems[i]->Destroy();
	}

	SpawnedItems.Empty();
	
	for (int i = 0; i < CurrentRoom.Entities.Num(); ++i)
	{
		CurrentRoom.Entities[i].CurrentHP = Entities[i]->GetHP();
		CurrentRoom.Entities[i].Position = Entities[i]->GetActorLocation();
		Entities[i]->ToggleEntity(false);
	}

	Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this))->UpdateRoom(CurrentRoom);
	
	CurrentRoom = Room;
	
	for (int i = 0; i < CurrentRoom.Entities.Num(); ++i)
	{
		if(!CurrentRoom.Entities[i].bActive || CurrentRoom.Entities[i].CurrentHP <= 0) continue;
		
		const auto Entity = Get(Room.Type);
		
		if(Entity != nullptr)
		{
			Entity->SetupEntity(CurrentRoom.Entities[i].Data);
			Entity->SetHealth_Implementation(CurrentRoom.Entities[i].CurrentHP);
			Entity->SetActorLocation(CurrentRoom.Entities[i].Position);
			Entity->ToggleEntity(true);

			UE_LOG(LogTemp, Display, TEXT("Loaded Entity with %f HPs"), Entity->GetHP());
		}
	}
}

void AEntityManager::DestroyItem(APickableActor* Pickable)
{
	if(SpawnedItems.Contains(Pickable))
		SpawnedItems.Remove(Pickable);

	if(Pickable->OnItemPicked.IsBound())	
		Pickable->OnItemPicked.RemoveDynamic(this, &AEntityManager::DestroyItem);
	
	Pickable->Destroy();
}

void AEntityManager::SpawnItem(const AEntity* Entity)
{
	const float Rand = FMath::RandRange(0.0f, 1.0f);

	if (Rand <= Entity->EntityDataAsset->ItemSpawnRate)
	{
		const auto PickableActor = GetWorld()->SpawnActor<APickableActor>(Entity->GetActorLocation(), Entity->GetActorRotation());
		
		UItem* Item = SpawnableItems[FMath::RandRange(0, SpawnableItems.Num() - 1)];
		
		PickableActor->Item = Item;
		PickableActor->SetupItem();

		PickableActor->OnItemPicked.AddDynamic(this, &AEntityManager::DestroyItem);
		
		SpawnedItems.Add(PickableActor);
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

	SpawnItem(Entity);
	
	Entity->ToggleEntity(false);
	Entity->SetActorLocation(GetActorLocation());

	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
	RoomSubsystem->OnEntityKilled.Broadcast(Entity->EntityDataAsset->ExperienceToGive);
}
