// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Setup")

	void Tick(float deltaTime) override;

	void BeginPlay() override;

	void AimTowardCrosshair() const;

	bool GetSightRayHitLocation(FVector& hitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingCOmponent(UTankAimingComponent* AimCompRef);

	UPROPERTY(EditDefaultsOnly)
		FVector2D CrossHairPosition;

	UPROPERTY(EditDefaultsOnly)
		float LookCheckLength;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.f;
};
