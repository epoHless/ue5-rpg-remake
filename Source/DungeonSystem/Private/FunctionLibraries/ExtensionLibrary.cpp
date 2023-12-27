#include "FunctionLibraries/ExtensionLibrary.h"

UExtensionLibrary::UExtensionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

bool UExtensionLibrary::LineTraceByMousePosition(const AGameModeBase* GameMode, FHitResult& HitResult)
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