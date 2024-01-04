#include "Inventory/Items/Effects/Implementations/ShieldEffect.h"
#include "Entities/Implementations/PlayerEntity.h"

void UShieldEffect::Execute_Implementation(AGameModeBase* GameMode, APlayerEntity* User)
{
	const auto Player = Cast<APlayerEntity>(User);

	if (Player)
	{
		Player->AddShield(25);
	}
}
