#include "Actors/Projectile.h"

#include "Data/ProjectileData.h"
#include "Entities/Interfaces/Damageable.h"
#include "Kismet/KismetMathLibrary.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->RegisterComponent();

	MovementComponent->ProjectileGravityScale = 0;
	MovementComponent->InitialSpeed = 100;
	MovementComponent->MaxSpeed = 100;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite Component"));
	SpriteComponent->SetRelativeRotation(FRotator(0,0, -90));

	SpriteComponent->SetMobility(EComponentMobility::Stationary);
	
	SpriteComponent->SetCollisionProfileName(TEXT("Projectile"));
	SpriteComponent->SetGenerateOverlapEvents(true);
}

void AProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
	{
		IDamageable::Execute_TakeDamage(OtherActor, ProjectileData->Damage, nullptr);
	}

	Destroy();
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SpriteComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlap);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::InitProjectile_Implementation(FVector Direction, UProjectileData* Data)
{
	ProjectileData = Data;
	SpriteComponent->SetSprite(Data->Sprite);

	auto Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + Direction * 20);
	Rotation.Roll = 0;
	Rotation.Yaw = -90;

	SetActorRelativeRotation(Rotation);

	MovementComponent->Velocity = Direction * Data->Speed;

	SpriteComponent->SetMobility(EComponentMobility::Movable);
}

