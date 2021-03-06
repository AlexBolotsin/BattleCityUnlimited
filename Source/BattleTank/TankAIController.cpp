// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (PlayerTank && ControlledTank)
	{
		MoveToActor(PlayerTank, 3000);

		UTankAimingComponent* aiming = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (aiming)
		{
			aiming->AimAt(PlayerTank->GetActorLocation());
			aiming->Fire();
		}
	}
}