#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Effects/StatusEffect.h"
#include "StatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatusCallback, UStatusEffect*, Effect);

class AEntity;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ENTITYSYSTEM_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatusComponent();

	UPROPERTY(BlueprintAssignable)
	FStatusCallback OnStatusAdded;

	UPROPERTY(BlueprintAssignable)
	FStatusCallback OnStatusRemoved;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<UStatusEffect*> ActiveStatuses;

	UPROPERTY()
	AEntity* Owner;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void AddStatus(UStatusEffect* Effect);
	void RemoveStatus(UStatusEffect* Effect);
};
