#pragma once

#include "CoreMinimal.h"
#include "RoomManagement/Data/RoomInstance.h"
#include "Subsystems/WorldSubsystem.h"
#include "RoomSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDungeonCallback, FRoomInstance, Room);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDirectionCallback, FIntVector, Direction);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExperienceCallback, float, Quantity);

UCLASS()
class DUNGEONSYSTEM_API URoomSubsystem : public UWorldSubsystem
{
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FExperienceCallback OnEntityKilled;
	
	UPROPERTY(BlueprintAssignable)
	FExperienceCallback OnExperienceGained;

	UPROPERTY(BlueprintAssignable)
	FExperienceCallback OnLevelUp;
	
	UPROPERTY(BlueprintAssignable)
	FDungeonCallback OnDungeonInit;
	
	UPROPERTY(BlueprintAssignable)
	FDungeonCallback OnRoomChanged;
	
	UPROPERTY(BlueprintAssignable)
	FDungeonCallback OnRoomCleared;

	UPROPERTY(BlueprintAssignable)
	FDungeonCallback OnUpdateRoomValues;

	UPROPERTY(BlueprintAssignable)
	FDirectionCallback OnBoundHit;
};
