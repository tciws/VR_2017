// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_2017.h"
#include "Engine.h"
#include "PlayerCharacter.h"
#include "UsableActor.h"


// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitialier) :
	m_isOperateCellphone(false),
	maxTraceDistance(200.0f),
	m_gotItemFlags(0),
	m_openAxis(160.0f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = ObjectInitialier.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCamera->AttachTo(GetRootComponent());

	//Position the camera a bit above the eyes
	FirstPersonCamera->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);

	//Allow the pawn to control rotation
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->PostProcessSettings.DepthOfFieldMethod = EDepthOfFieldMethod::DOFM_Gaussian;
	FirstPersonCamera->PostProcessSettings.DepthOfFieldFocalDistance = 100.0f;
	FirstPersonCamera->PostProcessSettings.bOverride_DepthOfFieldMethod = true;
	FirstPersonCamera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;

	m_UnderBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnderBodyMesh"));
	m_UnderBodyMesh->AttachTo(GetRootComponent());

	m_TurnAxis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurnAxis"));
	m_TurnAxis->AttachTo(m_UnderBodyMesh);

	m_TopBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopBodyMesh"));
	m_TopBodyMesh->AttachTo(m_TurnAxis);

	/*
	APPV = CreateDefaultSubobject<APostProcessVolume>(TEXT("APPV"));
	APPV->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale,TEXT("APPV"));
	APPV->bUnbound = false;
	APPV->Settings.DepthOfFieldMethod = EDepthOfFieldMethod::DOFM_BokehDOF;
	APPV->Settings.DepthOfFieldFocalDistance = 100.0f;
	*/
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_UnderBodyMesh->SetHiddenInGame(true);
	m_TurnAxis->SetHiddenInGame(true);
	m_TopBodyMesh->SetHiddenInGame(true);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isOperateCellphone)
	{
		if (m_openAxis > 0.0f)
		{
			m_openAxis -= openSpeed * DeltaTime;
			m_TurnAxis->SetRelativeRotation(FQuat(FRotator(0.0f, 0.0f, m_openAxis)));
			m_UnderBodyMesh->SetRelativeLocation(FVector(100.0f * (1 - m_openAxis / maxOpenAxis), 0.0f, 100.0f));
		}
	}
	else
	{
		if (m_openAxis < maxOpenAxis)
		{
			m_openAxis += openSpeed * DeltaTime;
			m_TurnAxis->SetRelativeRotation(FQuat(FRotator(0.0f, 0.0f, m_openAxis)));
			m_UnderBodyMesh->SetRelativeLocation(FVector(100.0f * (1 - m_openAxis / maxOpenAxis), 0.0f, 100.0f));
		}
	}
}

const float APlayerCharacter::maxOpenAxis = 160.0f;
const float APlayerCharacter::openSpeed = 180.0f;

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

	InputComponent->BindAction("OccurEvent", IE_Pressed, this, &APlayerCharacter::OccurEvent);

	InputComponent->BindAction("OpenCellphone", IE_Pressed, this, &APlayerCharacter::SetIsOperateCellphone);
}

void APlayerCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0) && !m_isOperateCellphone)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, value);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0) && !m_isOperateCellphone)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(Direction, value);
	}
}

void APlayerCharacter::OccurEvent()
{
	if (!m_isOperateCellphone)
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
		else if (!Usable)
		{
			GEngine->AddOnScreenDebugMessage(0, 15.f, FColor::Black, "Can not Trace");
		}
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

void APlayerCharacter::SetIsOperateCellphone()
{
	m_isOperateCellphone = !m_isOperateCellphone;
	//APPV->bUnbound = m_isOperateCellphone;
	m_UnderBodyMesh->SetHiddenInGame(!m_isOperateCellphone);
	m_TurnAxis->SetHiddenInGame(!m_isOperateCellphone);
	m_TopBodyMesh->SetHiddenInGame(!m_isOperateCellphone);
}