#pragma once

#include "CoreMinimal.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "Subsystems/WorldSubsystem.h"
#include "RoomSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDungeonCallback, FRoomInstance&, Room);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDirectionCallback, FIntVector, Direction);

UCLASS()
class DUNGEONSYSTEM_API URoomSubsystem : public UWorldSubsystem
{
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FDungeonCallback OnRoomChanged;

	UPROPERTY(BlueprintAssignable)
	FDungeonCallback OnUpdateRoomValues;

	UPROPERTY(BlueprintAssignable)
	FDirectionCallback OnBoundHit;
};
