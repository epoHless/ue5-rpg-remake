#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EntityController.generated.h"

UCLASS()
class ENTITYSYSTEM_API AEntityController : public APlayerController
{
protected:
	virtual void SetupInputComponent() override;

	void HorizontalMovement(float Value);
	void VerticalMovement(float Value);

	void SetInventorySlot(float X);
	void SetInventorySlotUp();
	void SetInventorySlotDown();
	void UseItem();

	void DealDamage();

	float HorizontalValue;
	float VerticalValue;

private:
	GENERATED_BODY()

public:
	AEntityController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
