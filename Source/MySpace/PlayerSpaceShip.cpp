// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceShip.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
APlayerSpaceShip::APlayerSpaceShip()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.0f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	// Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APlayerSpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		if (bZoomIn)
		{
			ZoomFactor += DeltaTime / 0.5f;
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;
		}

		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

		OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}

	// Rotate actor yaw
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	// Rotate camera pitch
	{
		FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		OurCameraSpringArm->SetWorldRotation(NewRotation); 
	}

	// Handle movement based on MoveX and MoveY axes
	{
		if (!MovementInput.IsZero())
		{
			// Scale movement
			MovementInput = MovementInput.SafeNormal() * 100.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void APlayerSpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayerSpaceShip::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APlayerSpaceShip::ZoomOut);

	InputComponent->BindAxis("MoveForward", this, &APlayerSpaceShip::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerSpaceShip::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &APlayerSpaceShip::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &APlayerSpaceShip::YawCamera);
}

void APlayerSpaceShip::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayerSpaceShip::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayerSpaceShip::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APlayerSpaceShip::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APlayerSpaceShip::ZoomIn()
{
	bZoomIn = true;
}

void APlayerSpaceShip::ZoomOut()
{
	bZoomIn = false;
}


