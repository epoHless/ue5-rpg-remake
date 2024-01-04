#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystems/RoomSubsystem.h"
#include "ExperienceComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ENTITYSYSTEM_API UExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UExperienceComponent();

	UPROPERTY(BlueprintAssignable)
	FExperienceCallback OnExperienceGained;

	UPROPERTY(BlueprintAssignable)
	FExperienceCallback OnLevelUp; 
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;
	
	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity|Experience")
	float MaxExperience = 100;

	UPROPERTY(VisibleAnywhere, Category = "RPG|Entity|Experience")
	float CurrentExperience = 0;
	
	UFUNCTION()
	void AddExperience(float Experience);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
