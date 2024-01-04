#include "Inventory/Items/Effects/Implementations/HealEffect.h"
#include "Entities/Implementations/PlayerEntity.h"

void UHealEffect::Execute_Implementation(AGameModeBase* GameMode, APlayerEntity* User)
{
	User->Execute_AddHP(User, 50);
}
