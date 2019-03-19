// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BarrelComponent.h"
#include "TurretComponent.h"
#include "TankAimingComponent.generated.h"


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
	// Called every frame
	void AimAt(FVector AimLocation, float LaunchSpeed);

	void SetBarrelReference(UBarrelComponent* Barrel);

	void SetTurretReference(UTurretComponent* Turret);

	void MoveBarrel(FVector AimDirection);
private:
	UBarrelComponent* BarrelComponent = nullptr;
	UTurretComponent* TurretComponent = nullptr;
};
