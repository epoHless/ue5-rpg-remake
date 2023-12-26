#include "RoomManagement/Actors/Bound.h"

#include "Components/BoxComponent.h"
#include "Entities/Implementations/PlayerEntity.h"

ABound::ABound()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetGenerateOverlapEvents(true);
}

void ABound::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto* Player = Cast<APlayerEntity>(OtherActor);

	if (Player)
	{
		OnPlayerOverlap.Broadcast(Direction);
	}
}

void ABound::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABound::OnCollision);
}

void ABound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}