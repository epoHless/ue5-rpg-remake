#include "Entities/Status System/StatusComponent.h"
#include "Entities/Entity.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AEntity>(GetOwner());
}

void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (int i = ActiveStatuses.Num() - 1; i >= 0; --i)
	{
		if(!ActiveStatuses.IsEmpty())
			ActiveStatuses[i]->Tick(DeltaTime, Owner);
	}
}

void UStatusComponent::AddStatus(UStatusEffect* Effect)
{
	if(!ActiveStatuses.Contains(Effect))
	{
		ActiveStatuses.Add(Effect);
		OnStatusAdded.Broadcast(Effect);
		
		Effect->OnAdded(Owner);
	}
}

void UStatusComponent::RemoveStatus(UStatusEffect* Effect)
{
	if(ActiveStatuses.Contains(Effect))
	{
		OnStatusRemoved.Broadcast(Effect);
		ActiveStatuses.Remove(Effect);

		Effect->OnRemoved(Owner);
	}
}
