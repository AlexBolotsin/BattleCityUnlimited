// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{
	if (!BarrelComponent)
		return;

	FVector LaunchVelocity(0.f);
	FVector StartLocation = BarrelComponent->GetSocketLocation(FName("Projectile"));
	
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation,
		AimLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		MoveBarrel(LaunchVelocity.GetSafeNormal());
	}
}

void UTankAimingComponent::SetBarrelReference(UBarrelComponent* Barrel)
{
	BarrelComponent = Barrel;
}


void UTankAimingComponent::SetTurretReference(UTurretComponent* Turret)
{
	TurretComponent = Turret;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator BarrelRotator = BarrelComponent->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	BarrelComponent->Elevate(DeltaRotator.Pitch);
	TurretComponent->Rotate(DeltaRotator.Yaw);
}