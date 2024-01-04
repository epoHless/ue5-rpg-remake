#include "Managers/EntityController.h"

#include "PaperFlipbookComponent.h"
#include "Entities/Implementations/EnemyEntity.h"
#include "Entities/Implementations/PlayerEntity.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Inventory/Inventory.h"
#include "Kismet/GameplayStatics.h"

void AEntityController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis(TEXT("Horizontal"), this, &AEntityController::HorizontalMovement);
	InputComponent->BindAxis(TEXT("Vertical"), this, &AEntityController::VerticalMovement);
	
	InputComponent->BindAction(TEXT("Damage"), IE_Pressed, this, &AEntityController::DealDamage); //TODO Temporary
	
	InputComponent->BindAction(TEXT("InventoryUp"), IE_Pressed, this, &AEntityController::SetInventorySlotUp);
	InputComponent->BindAction(TEXT("InventoryDown"), IE_Pressed, this, &AEntityController::SetInventorySlotDown); 
	InputComponent->BindAction(TEXT("UseItem"), IE_Pressed, this, &AEntityController::UseItem); 
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

void AEntityController::SetInventorySlotUp()
{
	const auto PlayerPawn = Cast<APlayerEntity>(GetPawn());
	PlayerPawn->GetInventory()->ChangeSlot(-1);
}

void AEntityController::SetInventorySlotDown()
{
	const auto PlayerPawn = Cast<APlayerEntity>(GetPawn());
	PlayerPawn->GetInventory()->ChangeSlot(1);
}

void AEntityController::UseItem()
{
	const auto PlayerPawn = Cast<APlayerEntity>(GetPawn());
	PlayerPawn->GetInventory()->UseItem();
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
	bShowMouseCursor = true;
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