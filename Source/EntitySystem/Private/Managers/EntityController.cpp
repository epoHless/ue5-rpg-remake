#include "Managers/EntityController.h"

#include "PaperFlipbookComponent.h"
#include "Entities/Implementations/PlayerEntity.h"
#include "GameFramework/PawnMovementComponent.h"

void AEntityController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis(TEXT("Horizontal"), this, &AEntityController::HorizontalMovement);
	InputComponent->BindAxis(TEXT("Vertical"), this, &AEntityController::VerticalMovement);
}

void AEntityController::HorizontalMovement(float Value)
{
	HorizontalValue = Value;
	
	UE_LOG(LogTemp, Warning, TEXT("horizontal value is: %f"), Value);
	Cast<APlayerEntity>(GetPawn())->GetSprite()->SetRelativeRotation(Value >= 0 ? FRotator(0,0,-90) : FRotator(180,0,-90));
}

void AEntityController::VerticalMovement(float Value)
{
	VerticalValue = Value;
	
	UE_LOG(LogTemp, Warning, TEXT("vertical value is: %f"), Value);
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