#include "RoomManagement/DungeonGameMode.h"
#include "Subsystems/RoomSubsystem.h"
#include "Entities/Implementations/PlayerEntity.h"
#include "FunctionLibraries/ExtensionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/EntityController.h"
#include "RoomManagement/Data/DungeonData.h"

void ADungeonGameMode::Cleanup()
{
	for (int i = 0; i < DungeonData->X * DungeonData->Y; i++) {
		delete[] Rooms[i];
	}
	delete[] Rooms;
}

ADungeonGameMode::ADungeonGameMode()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultPawnClass = APlayerEntity::StaticClass();
	PlayerControllerClass = AEntityController::StaticClass();
}

void ADungeonGameMode::BeginPlay()
{	
	Super::BeginPlay();

	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(this);
	RoomSubsystem->OnRoomCleared.AddDynamic(this, &ADungeonGameMode::IsGameOver);
}

void ADungeonGameMode::StartGame()
{
	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(this);
	RoomSubsystem->OnBoundHit.AddDynamic(this, &ADungeonGameMode::ChangeRoom);

	Rooms = new FRoomInstance*[DungeonData->X];
	
	for (int i = 0; i < DungeonData->X; i++)
	{
		Rooms[i] = new FRoomInstance[DungeonData->Y];
	}
	
	InitDungeon();

	CurrentRoom = Rooms[0][0];
	ChangeRoom(FIntVector::ZeroValue);

	RoomSubsystem->OnDungeonInit.Broadcast(CurrentRoom);
}

void ADungeonGameMode::UpdateRoom(const FRoomInstance& RoomInstance)
{
	Rooms[RoomInstance.Position.X][RoomInstance.Position.Y] = RoomInstance;
}

void ADungeonGameMode::SetDungeonData(UDungeonData* Data)
{
	DungeonData = Data;
}

void ADungeonGameMode::CalculateTotalWeight(float TotalSum, float& Random)
{
	for (const auto Template : DungeonData->Templates)
	{
		TotalSum += Template->Probability;
	}

	Random = FMath::RandRange(0.0f, TotalSum);
}

URoomTemplate* ADungeonGameMode::ChoseRoom()
{
	float TotalSum = 0;
	float Random;
	
	CalculateTotalWeight(TotalSum, Random);

	for (const auto Template : DungeonData->Templates)
	{
		if(Random < Template->Probability) return  Template;
		else Random = Random - Template->Probability;
	}

	return nullptr;
}

void ADungeonGameMode::InitDungeon()
{	
	const int32 ActualSize = DungeonData->X * DungeonData->Y;

	RoomsToClear = ActualSize - 1;
	
	FIntVector RoomPosition = FIntVector(0,0,0);

	for (int i = 0; i < ActualSize; i++)
	{
		const auto* Template = ChoseRoom();
		Rooms[RoomPosition.X][RoomPosition.Y] = FRoomInstance(Template, RoomPosition);
		
		RoomPosition.X++;

		if(RoomPosition.X >= DungeonData->X)
		{
			RoomPosition.X = 0;
			RoomPosition.Y++;
		}
	}
}

void ADungeonGameMode::ChangeRoom(FIntVector Direction)
{
	const FIntVector DestinationPosition = CurrentRoom.Position + Direction;

	if(DestinationPosition.X < 0 || DestinationPosition.X >= DungeonData->X) return;
	if(DestinationPosition.Y < 0 || DestinationPosition.Y >= DungeonData->Y) return;

	CurrentRoom = Rooms[DestinationPosition.X][DestinationPosition.Y];

	const auto Player = UGameplayStatics::GetPlayerPawn(this, 0);
	
	const auto Location = Player->GetActorLocation();
	Player->SetActorLocation(FVector(Location.X + (-Direction.X * TPLenght), Location.Y + (Direction.Y * TPLenght), Location.Z), false, nullptr, ETeleportType::ResetPhysics);

	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(this);
	RoomSubsystem->OnRoomChanged.Broadcast(CurrentRoom);

	UE_LOG(LogTemp, Warning, TEXT("Room X: %i Y: %i"), CurrentRoom.Position.X, CurrentRoom.Position.Y);
}

void ADungeonGameMode::IsGameOver(FRoomInstance Room)
{
	ClearedRooms++;

	if (ClearedRooms >= RoomsToClear)
	{
		OnGameOver.Broadcast(true);
	}
}
