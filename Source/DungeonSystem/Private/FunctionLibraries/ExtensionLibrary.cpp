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

FVector UExtensionLibrary::GetDirectionFromActor(const AGameModeBase* GameMode, AActor* Actor)
{
	FHitResult HitResult;
	
	const auto* Controller = GameMode->GetWorld()->GetFirstPlayerController();
	const auto CameraManager = Controller->PlayerCameraManager;
	
	float MouseX = 0;
	float MouseY = 0;

	Controller->GetMousePosition(MouseX, MouseY);

	FVector TraceLocation;
	FVector Direction = CameraManager->GetCameraRotation().Vector().GetSafeNormal();

	Controller->DeprojectScreenPositionToWorld(MouseX, MouseY, TraceLocation, Direction);

	const FVector EndLocation = TraceLocation + 10000 * Direction;
	
	if(GameMode->GetWorld()->LineTraceSingleByChannel(OUT HitResult, TraceLocation + Direction * 300 , EndLocation, ECC_Camera))
	{
		return  Actor->GetActorLocation() - HitResult.ImpactPoint;
	}
	else return FVector::ZeroVector;
}

TArray<FHitResult> UExtensionLibrary::SphereTraceByMousePosition(const AGameModeBase* GameMode, APlayerEntity* IgnoredActor,
                                                                 float Radius, float Range)
{
	const auto* Controller = GameMode->GetWorld()->GetFirstPlayerController();
	
	float MouseX = 0;
	float MouseY = 0;

	Controller->GetMousePosition(MouseX, MouseY);

	const FVector StartTrace = IgnoredActor->GetActorLocation();
	FVector EndTrace = StartTrace;
	
	FVector TraceLocation;
	FVector Direction = GetDirectionFromActor(GameMode, IgnoredActor);

	// Controller->DeprojectMousePositionToWorld(TraceLocation, Direction);

	TraceLocation.Z = 15;
	
	Direction.Normalize();
	
	UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), Direction.X, Direction.Y, Direction.Z);
	
	EndTrace = StartTrace + (Direction + Range);

	TArray<AActor*> Ignored;
	Ignored.Add(IgnoredActor);
	
	TArray<FHitResult> Results;
	
	UKismetSystemLibrary::SphereTraceMulti(GameMode->GetWorld(), IgnoredActor->GetActorLocation(), EndTrace, Radius, UEngineTypes::ConvertToTraceType(ECC_Camera), false,
		Ignored, EDrawDebugTrace::ForDuration, Results, true);

	return Results;
}