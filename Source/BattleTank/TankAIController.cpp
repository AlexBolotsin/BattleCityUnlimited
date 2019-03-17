// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("GOT PLAYER"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("COULDNT FIND PLAYA"));
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}