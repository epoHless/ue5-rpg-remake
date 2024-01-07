#include "Experience/ExperienceComponent.h"

#include "FunctionLibraries/ExtensionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/RoomSubsystem.h"

UExperienceComponent::UExperienceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UExperienceComponent::AddExperience(float Experience)
{
	CurrentExperience += Experience;

	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));

	if(CurrentExperience >= MaxExperience)
	{
		const float LeftOver = FMath::Abs(MaxExperience - CurrentExperience);

		MaxExperience += 25;
		CurrentExperience = LeftOver;

		Level++;
		
		RoomSubsystem->OnLevelUp.Broadcast(Level);
	}

	RoomSubsystem->OnExperienceGained.Broadcast(CurrentExperience/MaxExperience);
}

void UExperienceComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto RoomSubsystem = UExtensionLibrary::GetSubsystemByGameMode<URoomSubsystem>(UGameplayStatics::GetGameMode(this));
	RoomSubsystem->OnEntityKilled.AddDynamic(this, &UExperienceComponent::AddExperience);
}

