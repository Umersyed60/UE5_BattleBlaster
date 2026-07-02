// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting Spring Arm Component For Player Follow Camera
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(CapsuleComp);

	//Setting Player Follow Camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//Setting Enhanced Input's Default Mapping Context
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer()) {
			if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)) {
				SubSystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	//Making Player Disabled Before Timer Ends
	SetPlayerEnabled(false);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//To Rotate Tank Turrent Along With Mouse Position
	if (PlayerController) {
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		//Passing Mouse Cursor Values To Rotate Tank Turret in BasicPawn Class
		RotateTurrent(HitResult.ImpactPoint);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.0f, 12, FColor::Red);
	}

}

// Called to bind Player Movement Action to Relative Functions
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhanceInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhanceInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		EnhanceInputComp->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::TurnInput);
		EnhanceInputComp->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
}

//Function To Move Tank In World On User Input
void ATank::MoveInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();

	FVector DeltaLocation = FVector(0.0f, 0.0f, 0.0f);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	DeltaLocation.X = Speed * InputValue * DeltaTime;
	AddActorLocalOffset(DeltaLocation, true);
}

//Function To Rotate Tank In World On User Input
void ATank::TurnInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();

	FRotator DeltaRotation = FRotator(0.0f, 0.0f, 0.0f);
	DeltaRotation.Yaw = TurnRate * InputValue * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(DeltaRotation, true);
}

//Function To Handle Player Tank Destruction
void ATank::HandleDestruction() {
	Super::HandleDestruction();

	IsAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);
}

//Function Call To Enable/Disable Player Input
void ATank::SetPlayerEnabled(bool Enabled)
{
	if (PlayerController) {
		if (Enabled) {
			EnableInput(PlayerController);
		}
		else {
			DisableInput(PlayerController);
		}
		PlayerController->SetShowMouseCursor(Enabled);
	}
}
