#include "RoomManagement/Actors/DungeonManager.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"

ADungeonManager::ADungeonManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADungeonManager::OnOverlap(FIntVector Direction)
{
	ChangeRoom(Direction);
}

void ADungeonManager::InitDungeon()
{
	for (const auto Bound : Bounds)
	{
		Bound->OnPlayerOverlap.AddDynamic(this, &ADungeonManager::OnOverlap);
	}
	
	const int32 ActualSize = 10 * 10;
	FIntVector RoomPosition = FIntVector(0,0,0);
	
	for (int i = 0; i < ActualSize; i++)
	{
		const auto* Template = Templates[FMath::RandRange(0, Templates.Num() - 1)];
		Rooms[RoomPosition.X][RoomPosition.Y] = FRoomInstance(Template, RoomPosition);
		
		RoomPosition.X++;

		if(RoomPosition.X >= 10)
		{
			RoomPosition.X = 0;
			RoomPosition.Y++;
		}
	}
}

void ADungeonManager::ChangeRoom(FIntVector Direction)
{
	const FIntVector DestinationPosition = CurrentRoom.Position + Direction;

	if(DestinationPosition.X < 0 || DestinationPosition.X >= 10) return;
	if(DestinationPosition.Y < 0 || DestinationPosition.Y >= 10) return;

	CurrentRoom = Rooms[DestinationPosition.X][DestinationPosition.Y];

	TilemapActor->GetRenderComponent()->SetTileMap(CurrentRoom.TileMap);

	OnRoomChanged.Broadcast(CurrentRoom);
}

void ADungeonManager::BeginPlay()
{
	Super::BeginPlay();

	InitDungeon();

	CurrentRoom = Rooms[0][0];
	ChangeRoom(FIntVector::ZeroValue);
}

void ADungeonManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

