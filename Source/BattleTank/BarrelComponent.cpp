// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrelComponent.h"

void UBarrelComponent::Elevate(float RelativeSpeed)
{
	auto ElevationChange = FMath::Clamp(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChange, MinElevation, MaxElevation);
	
	SetRelativeRotation(FRotator(RawNewElevation, 0.f, 0.f));
}