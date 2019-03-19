// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UBarrelComponent* Barrel)
{
	AimingComponent->SetBarrelReference(Barrel);
	BarrelComponent = Barrel;
}

void ATank::SetTurretReference(UTurretComponent* Turret)
{
	AimingComponent->SetTurretReference(Turret);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE!"));

	if (!BarrelComponent)
		return;

	AProjectile* projectileInst = GetWorld()->SpawnActor<AProjectile>(ProjectileBP,
		BarrelComponent->GetSocketLocation(FName("Projectile")),
		BarrelComponent->GetSocketRotation(FName("Projectile")));

	projectileInst->Launch(LaunchSpeed);
}