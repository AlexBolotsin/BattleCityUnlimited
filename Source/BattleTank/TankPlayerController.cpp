// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::AimTowardCrosshair() const
{
	UE_LOG(LogTemp, Warning, TEXT("AimTowardCrosshair"));
	if (!GetControlledTank())
		return;

	FVector HitLocation(0.0f, 0.0f, 0.0f);
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT LOCATION %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	UE_LOG(LogTemp, Warning, TEXT("GetSightRayHitLocation"));

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
	UE_LOG(LogTemp, Warning, TEXT("GetLookDirection %s"), *ScreenLocation.ToString());
	FVector WorldPosition;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldPosition, LookDirection);
}
#include "DrawDebugHelpers.h"
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	UE_LOG(LogTemp, Warning, TEXT("GetLookVectorHitLocation %s"), *LookDirection.ToString());
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