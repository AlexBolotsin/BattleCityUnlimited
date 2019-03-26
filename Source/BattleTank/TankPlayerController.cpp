// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
		FoundAimingCOmponent(AimingComponent);
}

void ATankPlayerController::AimTowardCrosshair() const
{
	auto ControlledTank = GetPawn();
	if (!ControlledTank)
		return;

	FVector HitLocation(0.0f, 0.0f, 0.0f);
	if (GetSightRayHitLocation(HitLocation))
	{
		UTankAimingComponent* aiming = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (aiming)
		{
			aiming->UpdateFireState();
			aiming->AimAt(HitLocation);
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX*CrossHairPosition.X, ViewportSizeY*CrossHairPosition.Y);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection) && GetLookVectorHitLocation(LookDirection, HitLocation))
	{
		return true;
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldPosition;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldPosition, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult hitResult;
	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + LookDirection * LookCheckLength;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, TraceStart, TraceEnd, ECC_Visibility))
	{
		HitLocation = hitResult.Location;
		return true;
	}

	return false;
}