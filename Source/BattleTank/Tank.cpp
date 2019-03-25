// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	UTankAimingComponent* aiming = FindComponentByClass<UTankAimingComponent>();
	if (aiming)
		aiming->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	UBarrelComponent* BarrelComponent = FindComponentByClass<UBarrelComponent>();

	if (!BarrelComponent || !isReloaded)
		return;

	AProjectile* projectileInst = GetWorld()->SpawnActor<AProjectile>(ProjectileBP,
		BarrelComponent->GetSocketLocation(FName("Projectile")),
		BarrelComponent->GetSocketRotation(FName("Projectile")));

	projectileInst->Launch(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}