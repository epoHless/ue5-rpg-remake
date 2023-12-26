#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bound.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCollisionCallback, FIntVector, Direction);

class UBoxComponent;

UCLASS(Blueprintable, BlueprintType)
class DUNGEONSYSTEM_API ABound : public AActor
{
	GENERATED_BODY()

public:
	ABound();

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(BlueprintAssignable)
	FCollisionCallback OnPlayerOverlap;

protected:
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "RPG|Dungeon System")
	FIntVector Direction;
	
public:
	virtual void Tick(float DeltaTime) override;
};
