#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ENTITYSYSTEM_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UProjectileData* ProjectileData;

	UFUNCTION(BlueprintNativeEvent)
	void InitProjectile(FVector Direction, UProjectileData* Data);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;
};
