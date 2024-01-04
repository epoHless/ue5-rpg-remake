﻿#include "Inventory/Pickables/PickableActor.h"

#include "Inventory/Items/Item.h"
#include "PaperSpriteComponent.h"
#include "Entities/Implementations/PlayerEntity.h"
#include "Inventory/Inventory.h"

void APickableActor::OnPickup_Implementation(APlayerEntity* PlayerEntity)
{
	PlayerEntity->GetInventory()->AddItem(Item);
	OnItemPicked.Broadcast(this);
}

APickableActor::APickableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite Component"));
	SpriteComponent->SetupAttachment(GetRootComponent());
	SpriteComponent->RegisterComponent();
	
	SpriteComponent->SetMobility(EComponentMobility::Stationary);
	
	SpriteComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	SpriteComponent->SetGenerateOverlapEvents(true);

	SpriteComponent->SetRelativeRotation(FRotator(270,0,0));
}

void APickableActor::SetupItem()
{
	SpriteComponent->SetSprite(Item->Sprite);
}

void APickableActor::BeginPlay()
{
	Super::BeginPlay();
}