#include "RoomManagement/DungeonGameMode.h"
#include "Subsystems/RoomSubsystem.h"
#include "Entities/Implementations/PlayerEntity.h"
#include "FunctionLibraries/ExtensionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/EntityController.h"

void ADungeonGameMode::Cleanup()
{
	for (int i = 0; i < XSize * YSize; ++i) {
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

void ADungeonGameMode::StartGame()
{
	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(this);
	RoomSubsystem->OnBoundHit.AddDynamic(this, &ADungeonGameMode::ChangeRoom);

	Rooms = new FRoomInstance*[XSize];
	for (int i = 0; i < XSize; ++i) {
		Rooms[i] = new FRoomInstance[YSize];
	}
	
	InitDungeon();

	CurrentRoom = Rooms[0][0];
	ChangeRoom(FIntVector::ZeroValue);

	RoomSubsystem->OnDungeonInit.Broadcast(CurrentRoom);
}

void ADungeonGameMode::BeginPlay()
{	
	Super::BeginPlay();
}

void ADungeonGameMode::UpdateRoom(const FRoomInstance& RoomInstance)
{
	Rooms[RoomInstance.Position.X][RoomInstance.Position.Y] = RoomInstance;
}

void ADungeonGameMode::InitDungeon()
{	
	const int32 ActualSize = XSize * YSize;
	FIntVector RoomPosition = FIntVector(0,0,0);
	
	for (int i = 0; i < ActualSize; i++)
	{
		const auto* Template = Templates[FMath::RandRange(0, Templates.Num() - 1)];
		Rooms[RoomPosition.X][RoomPosition.Y] = FRoomInstance(Template, RoomPosition);
		
		RoomPosition.X++;

		if(RoomPosition.X >= XSize)
		{
			RoomPosition.X = 0;
			RoomPosition.Y++;
		}
	}
}

void ADungeonGameMode::ChangeRoom(FIntVector Direction)
{
	const FIntVector DestinationPosition = CurrentRoom.Position + Direction;

	if(DestinationPosition.X < 0 || DestinationPosition.X >= XSize) return;
	if(DestinationPosition.Y < 0 || DestinationPosition.Y >= YSize) return;

	CurrentRoom = Rooms[DestinationPosition.X][DestinationPosition.Y];

	const auto Player = UGameplayStatics::GetPlayerPawn(this, 0);
	
	const auto Location = Player->GetActorLocation();
	Player->SetActorLocation(FVector(Location.X + (-Direction.X * TPLenght), Location.Y + (Direction.Y * TPLenght), Location.Z), false, nullptr, ETeleportType::ResetPhysics);

	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(this);
	RoomSubsystem->OnRoomChanged.Broadcast(CurrentRoom);

	UE_LOG(LogTemp, Warning, TEXT("Room X: %i Y: %i"), CurrentRoom.Position.X, CurrentRoom.Position.Y);
}
