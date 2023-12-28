#include "Managers/EntityController.h"

#include "PaperFlipbookComponent.h"
#include "Entities/Implementations/EnemyEntity.h"
#include "Entities/Implementations/PlayerEntity.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AEntityController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis(TEXT("Horizontal"), this, &AEntityController::HorizontalMovement);
	InputComponent->BindAxis(TEXT("Vertical"), this, &AEntityController::VerticalMovement);
	
	InputComponent->BindAction(TEXT("Damage"), IE_Pressed, this, &AEntityController::DealDamage);
}

void AEntityController::HorizontalMovement(float Value)
{
	HorizontalValue = Value;
	Cast<APlayerEntity>(GetPawn())->GetSprite()->SetRelativeRotation(Value >= 0 ? FRotator(0,0,-90) : FRotator(180,0,-90));
}

void AEntityController::VerticalMovement(float Value)
{
	VerticalValue = Value;
}

void AEntityController::DealDamage()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyEntity::StaticClass(), Enemies);

	for (const auto Enemy : Enemies)
	{
		IDamageable::Execute_TakeDamage(Enemy, 10);
	}
}


AEntityController::AEntityController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEntityController::BeginPlay()
{
	Super::BeginPlay();
}

void AEntityController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetPawn()->GetMovementComponent()->Velocity = HorizontalValue == 0 && VerticalValue == 0 ?
		FVector::ZeroVector :
		FVector(HorizontalValue * 100, -VerticalValue * 100, 0);
}