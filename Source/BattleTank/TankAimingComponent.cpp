// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::UpdateFireState()
{
	EFiringState newState = EFiringState::Reloading;
	if (!isReloaded)
	{
		newState = EFiringState::Reloading;
	}
	else if (FinishedAiming)
	{
		newState = EFiringState::Locked;
	}
	else
	{
		newState = EFiringState::Aiming;
	}

	if (FiringState != newState)
	{
		FiringState = newState;
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	UpdateFireState();
}

void UTankAimingComponent::AimAt(FVector AimLocation)
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

void UTankAimingComponent::Initialise(UTurretComponent* turret, UBarrelComponent* barrel)
{
	TurretComponent = turret;
	BarrelComponent = barrel;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator BarrelRotator = BarrelComponent->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;
	BarrelComponent->Elevate(DeltaRotator.Pitch);
	TurretComponent->Rotate(DeltaRotator.Yaw);

	if (DeltaRotator.Pitch < 0.1f && DeltaRotator.Yaw < 0.1f)
		FinishedAiming = true;
	else
		FinishedAiming = false;
}


void UTankAimingComponent::Fire()
{
	if (!BarrelComponent || !isReloaded || !FinishedAiming)
		return;

	AProjectile* projectileInst = GetWorld()->SpawnActor<AProjectile>(ProjectileBP,
		BarrelComponent->GetSocketLocation(FName("Projectile")),
		BarrelComponent->GetSocketRotation(FName("Projectile")));

	projectileInst->Launch(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}