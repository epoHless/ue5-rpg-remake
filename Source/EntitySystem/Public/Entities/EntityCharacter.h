#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Interfaces/Spawnable.h"

#include "EntityCharacter.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API AEntityCharacter : public APaperCharacter, public ISpawnable
{
	GENERATED_BODY()

public:
	AEntityCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
