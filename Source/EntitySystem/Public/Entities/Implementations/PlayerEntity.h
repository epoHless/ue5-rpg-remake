﻿#pragma once

#include "CoreMinimal.h"
#include "Entities/Entity.h"
#include "PlayerEntity.generated.h"

UCLASS()
class ENTITYSYSTEM_API APlayerEntity : public AEntity
{
	GENERATED_BODY()

public:
	APlayerEntity();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};