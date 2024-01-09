#include "FunctionLibraries/ExtensionLibrary.h"

#include "Entities/Implementations/PlayerEntity.h"
#include "Kismet/KismetSystemLibrary.h"

UExtensionLibrary::UExtensionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

bool UExtensionLibrary::LineTraceByMousePosition(const AGameModeBase* GameMode, FVector StartTrace, FHitResult& HitResult)
{
	const auto* Controller = GameMode->GetWorld()->GetFirstPlayerController();
	const auto CameraManager = Controller->PlayerCameraManager;
	
	float MouseX = 0;
	float MouseY = 0;

	Controller->GetMousePosition(MouseX, MouseY);

	FVector TraceLocation;
	FVector Direction = CameraManager->GetCameraRotation().Vector().GetSafeNormal();

	Controller->DeprojectScreenPositionToWorld(MouseX, MouseY, TraceLocation, Direction);

	FVector EndLocation = TraceLocation + 10000 * Direction;
	
	return GameMode->GetWorld()->LineTraceSingleByChannel(OUT HitResult, TraceLocation + Direction * 300 , EndLocation, ECC_Camera); 
}

FVector2D UExtensionLibrary::GetMousePosition(const APlayerController* Controller, AActor* Actor)
{
	float MouseX = 0;
	float MouseY = 0;

	Controller->GetMousePosition(MouseX, MouseY);

	return FVector2D(MouseX, MouseY);
}

TArray<FHitResult> UExtensionLibrary::SphereTraceByMousePosition(const AGameModeBase* GameMode, APlayerEntity* IgnoredActor,
                                                                 float Radius, float Range)
{
	const auto* Controller = GameMode->GetWorld()->GetFirstPlayerController();
	
	FVector2D ScreenLocation;
	Controller->ProjectWorldLocationToScreen(IgnoredActor->GetActorLocation(), ScreenLocation, true);
	
	FVector2D Direction = GetMousePosition(Controller, IgnoredActor) - ScreenLocation;
	Direction.Normalize();

	const FVector EndLocation = IgnoredActor->GetActorLocation() + (FVector(Direction.X, Direction.Y, 15) * Range);

	TArray<AActor*> Ignored;
	Ignored.Add(IgnoredActor);
	
	TArray<FHitResult> Results;
	
	UKismetSystemLibrary::SphereTraceMulti(GameMode->GetWorld(), IgnoredActor->GetActorLocation(), FVector(EndLocation.X, EndLocation.Y, 0), Radius, UEngineTypes::ConvertToTraceType(ECC_Camera), false,
		Ignored, EDrawDebugTrace::None, Results, true);

	return Results;
}