// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
class UTrackComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTrackComponent* Left, UTrackComponent* Right);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float Throw);

private:
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);

	UTrackComponent* LeftTrack = nullptr;
	UTrackComponent* RightTrack = nullptr;
};
