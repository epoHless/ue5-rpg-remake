#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtensionLibrary.generated.h"

class APlayerEntity;

UCLASS()
class DUNGEONSYSTEM_API UExtensionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, Category = "Chimera|Input System")
	static bool LineTraceByMousePosition(const AGameModeBase* GameMode, FVector StartTrace, FHitResult& HitResult);
	static FVector GetDirectionFromActor(const AGameModeBase* GameMode, AActor* Actor);
	static TArray<FHitResult> SphereTraceByMousePosition(const AGameModeBase* GameMode, APlayerEntity* IgnoredActor,
	                                                     float Radius, float Range);

	template<typename T>
	static T* GetSubsystemByGameInstance(const AGameModeBase* GameMode)
	{
		const auto* GameInstance = GameMode->GetWorld()->GetGameInstance();
	
		if(GameInstance)
		{
			return GameInstance->GetSubsystem<T>();
		}

		return nullptr;
	}

	template<typename T>
	static T* GetSubsystemByGameMode(const AGameModeBase* GameMode)
	{
		return GameMode->GetWorld()->GetSubsystem<T>();
	}
};
