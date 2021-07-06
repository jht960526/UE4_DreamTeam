// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "GameFramework/PlayerController.h"
//#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Boom(pulls towards the player if there's a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f; // Camera follows at this distance
	CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on comtroller

	// Create Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	
	// Atach the camera to the end of the boom and let the boom adjust to match
	// the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // 카메라가 컨트롤러가 아닌 카메라붐을 따라가야함

	// Set our turn rates for input
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward",this,&AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AMain::MoveRight);

	PlayerInputComponent->BindAxis("Trun",this, &APawn::AddControllerYawInput);
	// 마우스 움직임은 컨트롤러가 움직임 -> 컨트롤러는 폰을 움직이니까
	PlayerInputComponent->BindAxis("LookUp",this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate",this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate",this,&AMain::LookUpAtRate);

}

void AMain::MoveForward(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// 현재 캐릭터의 회전 매트릭스를 구함. (각 축이 얼마나 회전되었는지) 유닛의 x축 길이 구하기
		AddMovementInput(Direction,Value);
	}
}

void AMain::MoveRight(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// 현재 캐릭터의 회전 매트릭스를 구함. (각 축이 얼마나 회전되었는지) 유닛의 y축 길이 구하기
		AddMovementInput(Direction,Value);
	}
}

void AMain::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

