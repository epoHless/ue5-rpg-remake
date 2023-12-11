#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Spawnable.h"
#include "InteractableActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API AInteractableActor : public AActor, public ISpawnable
{
	GENERATED_BODY()

public:
	AInteractableActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
