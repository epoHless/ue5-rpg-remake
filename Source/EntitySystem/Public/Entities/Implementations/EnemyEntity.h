﻿#pragma once

#include "CoreMinimal.h"
#include "Entities/Entity.h"
#include "Entities/Interfaces/Spawnable.h"
#include "EnemyEntity.generated.h"

UCLASS()
class ENTITYSYSTEM_API AEnemyEntity : public AEntity, public ISpawnable
{
	GENERATED_BODY()

public:
	AEnemyEntity();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
