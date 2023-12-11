#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "Entity.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API AEntity : public APaperCharacter
{
	GENERATED_BODY()

public:
	AEntity();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
