// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPawn.h"

// Sets default values
ABasicPawn::ABasicPawn()
{
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
}

void ABasicPawn::RotateTurrent(FVector LookAtTarget)
{
	FVector VectorToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, VectorToTarget.Rotation().Yaw, 0.0f);

	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 20.0f);

	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

