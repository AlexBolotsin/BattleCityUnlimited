// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BarrelComponent.h"
#include "TurretComponent.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTurretComponent* turret, UBarrelComponent* barrel);

	// Called every frame
	void AimAt(FVector AimLocation);
	void MoveBarrel(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void Fire();

	void UpdateFireState();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "FiringState")
		EFiringState FiringState = EFiringState::Locked;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		double ReloadTime = 3.f;

	double LastFireTime = 0.f;

private:
	UBarrelComponent* BarrelComponent = nullptr;
	UTurretComponent* TurretComponent = nullptr;

	bool FinishedAiming = false;
};
