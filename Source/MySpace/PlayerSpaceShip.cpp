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

}

// Called to bind functionality to input
void APlayerSpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

