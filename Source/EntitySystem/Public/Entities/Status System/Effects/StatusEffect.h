#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StatusEffect.generated.h"

class UPaperSprite;
class AEntity;

UCLASS(Blueprintable, BlueprintType, Abstract)
class ENTITYSYSTEM_API UStatusEffect : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (UIMin = 1, UIMax = 10))
	int32 Cycles;

	int32 CurrentCycles = 0;

	UPROPERTY(EditAnywhere)
	float Duration;

	float CurrentTime = 0;
	
public:

	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0, UIMax = 1.0))
	float Probability = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Icon;

	void Tick(float& DeltaTime, AEntity* Entity);

	void OnAdded()
	{
		CurrentTime = 0;
		CurrentCycles = 0;
	}

	UFUNCTION(BlueprintNativeEvent)
	void OnCycleComplete(AEntity* Entity);
};
