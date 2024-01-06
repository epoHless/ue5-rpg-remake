#include "Entities/Status System/Effects/StatusEffect.h"

#include "Entities/Entity.h"
#include "Entities/Status System/StatusComponent.h"

void UStatusEffect::OnCycleComplete_Implementation(AEntity* Entity)
{
}

void UStatusEffect::Tick(float& DeltaTime, AEntity* Entity)
{
	CurrentTime += DeltaTime;

	if (CurrentTime >= Duration)
	{
		OnCycleComplete(Entity);

		CurrentTime = 0;
		CurrentCycles++;

		if (CurrentCycles >= Cycles)
		{
			Entity->GetStatusComponent()->RemoveStatus(this);
		}
	}
}
