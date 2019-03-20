// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackComponent.h"

void UTrackComponent::SetTrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("Throttling %f"), Throttle);

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}