#include "Inventory/Items/Effects/Implementations/SwordEffect.h"

#include "Entities/Entity.h"
#include "FunctionLibraries/ExtensionLibrary.h"

void USwordEffect::Execute_Implementation(AGameModeBase* GameMode, APlayerEntity* User)
{
	const auto Results = UExtensionLibrary::SphereTraceByMousePosition(GameMode, User, 10, 20);
	
	if(Results.Num() > 0)
	{
		for (auto Result : Results)
		{
			if(Result.GetActor()->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
			{
				IDamageable::Execute_TakeDamage(Result.GetActor(), 30);
			}
		}
	}
}
