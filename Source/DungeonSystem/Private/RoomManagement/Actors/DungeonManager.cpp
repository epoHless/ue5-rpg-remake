#include "RoomManagement/Actors/DungeonManager.h"

ADungeonManager::ADungeonManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADungeonManager::OnOverlap(FVector2D Direction)
{
	ChangeRoom(Direction);
}

void ADungeonManager::InitDungeon()
{
	for (const auto Bound : Bounds)
	{
		Bound->OnPlayerOverlap.AddDynamic(this, &ADungeonManager::OnOverlap);
	}
	
	const int32 ActualSize = XSize * YSize;
	FVector2D RoomPosition;
	
	for (int i = 0; i < ActualSize; i++)
	{
		const auto* Template = Templates[FMath::RandRange(0, Templates.Num() - 1)];
		Rooms.Add(FRoomInstance(false, Template->TileMap, RoomPosition));
		
		RoomPosition.X++;

		if(RoomPosition.X > XSize)
		{
			RoomPosition.X = 0;
			RoomPosition.Y++;
		}
	}
}

void ADungeonManager::ChangeRoom(FVector2D Direction)
{
	FVector2D CurrentPosition = CurrentRoom.Position;

	const auto room = Rooms.FindByPredicate([&Direction, &CurrentPosition](const FRoomInstance& Instance)
	{
		return Instance.Position == (Direction + CurrentPosition);
	});

	CurrentRoom = *room;

	OnRoomChanged.Broadcast(CurrentRoom);
}

void ADungeonManager::BeginPlay()
{
	Super::BeginPlay();

	InitDungeon();
}

void ADungeonManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

