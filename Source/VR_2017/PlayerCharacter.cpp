// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_2017.h"
#include "Engine.h"
#include "PlayerCharacter.h"
#include "UsableActor.h"


// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitialier) :
	m_isOpeningDoor(false),
	maxTraceDistance(800.0f),
	m_gotItemFlags(0)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = ObjectInitialier.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCamera->AttachTo(GetRootComponent());

	//Position the camera a bit above the eyes
	FirstPersonCamera->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);

	//Allow the pawn to control rotation
	FirstPersonCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

	InputComponent->BindAction("OccurEvent", IE_Pressed, this, &APlayerCharacter::OccurEvent);
}

void APlayerCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, value);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(Direction, value);
	}
}

void APlayerCharacter::OpenDoor()
{
	m_isOpeningDoor = true;

	if (m_isOpeningDoor)
	{
		GEngine->AddOnScreenDebugMessage(0, 15.f, FColor::Black, "The Door Open!");
	}
}

void APlayerCharacter::OccurEvent()
{
	AUsableActor* Usable = GetUsableInView();
	ItemName item;

	if (Usable)
	{
		item = Usable->Event();
		if (item != ItemName::noItem)
		{
			PickupItem(item);
		}
		//GEngine->AddOnScreenDebugMessage(0, 15.f, FColor::Black, FString::Printf(TEXT("flag is %d"), m_gotItemFlags));
	}
	else if(!Usable)
	{
		GEngine->AddOnScreenDebugMessage(0, 15.f, FColor::Black, "Can not Trace");
	}
}

AUsableActor* APlayerCharacter::GetUsableInView()
{
	FVector CameraLoc;
	FRotator CameraRot;

	if (Controller == NULL)
		return NULL;

	Controller->GetPlayerViewPoint(CameraLoc, CameraRot);
	const FVector TraceStart = CameraLoc;
	const FVector Direction = CameraRot.Vector();
	const FVector TraceEnd = TraceStart + (Direction * maxTraceDistance);

	FCollisionQueryParams *TraceParams = new FCollisionQueryParams;

	FHitResult *Hit = new FHitResult;
	GetWorld()->LineTraceSingleByChannel(*Hit, TraceStart, TraceEnd, ECC_Visibility, *TraceParams);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, true);

	return Cast<AUsableActor>(Hit->GetActor());
}

void APlayerCharacter::PickupItem(ItemName itemName)
{
	m_gotItemFlags |= (1 << static_cast<int>(itemName));
}

void APlayerCharacter::LoseItem(ItemName itemName)
{
	m_gotItemFlags &= ~(1 << static_cast<int>(itemName));
}