// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPawn.h"
#include "InputMappingContext.h"

// Sets default values
ABasicPawn::ABasicPawn()
{
	//Setting Hirarchy Of Meshes For Player Tank And Enemy Turret Objects
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

//Function To Rotate Player Tank and Enemy Cannon Turret
void ABasicPawn::RotateTurrent(FVector LookAtTarget)
{
	FVector VectorToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, VectorToTarget.Rotation().Yaw, 0.0f);

	//InterPolated Rotation for Smooth Rotation of Turret
	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 20.0f);

	//Setting Turret Rotation
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

//Function To Fire Projectile
void ABasicPawn::Fire()
{
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	//DrawDebugSphere(GetWorld(), SpawnLocation, 25.0f, 12, FColor::Red, false, 3.0f);

	//Spawning Projectile And Setting Position And Rotation
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	if (Projectile) {
		Projectile->SetOwner(this);
	}
}

void ABasicPawn::HandleDestruction() {

}

