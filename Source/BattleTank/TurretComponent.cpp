// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretComponent.h"

void UTurretComponent::Rotate(float RelativeSpeed)
{
	auto RotationChange = FMath::Clamp(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation(FRotator(0.f, RelativeRotation.Yaw + RotationChange, 0.f));
}