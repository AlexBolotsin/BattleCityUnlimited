// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TrackComponent.h"

void UTankMovementComponent::Initialise(UTrackComponent* Left, UTrackComponent* Right)
{
	if (!Left || !Right)
		return;

	LeftTrack = Left;
	RightTrack = Right;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
		return;

	FVector dir;
	float lenght;
	GetOwner()->GetVelocity().ToDirectionAndLength(dir, lenght);

	//if (lenght < 600.f)
	{
		LeftTrack->SetTrottle(Throw);
		RightTrack->SetTrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
		return;
	FVector dir;
	float lenght;
	GetOwner()->GetVelocity().ToDirectionAndLength(dir, lenght);

	//if (lenght < 600.f)
	{
		LeftTrack->SetTrottle(Throw);
		RightTrack->SetTrottle(-Throw);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntentaion = MoveVelocity.GetSafeNormal();

	auto DotProd = FVector::DotProduct(TankForward, AIForwardIntentaion);
	auto CrossProd = FVector::CrossProduct(TankForward, AIForwardIntentaion);

	IntendMoveForward(DotProd);
	IntendTurnRight(CrossProd.Z);
}