// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_2017.h"
#include "CellphoneManager.h"

// Sets default values
ACellphoneManager::ACellphoneManager() : 
	m_openAngle(0.0f),
	m_isOpening(false),
	m_isClosing(false)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_UnderBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnderBodyMesh"));
	m_UnderBodyMesh->AttachTo(GetRootComponent());

	m_TurnAxis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurnAxis"));
	m_TurnAxis->AttachTo(m_UnderBodyMesh);

	m_TopBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopBodyMesh"));
	m_TopBodyMesh->AttachTo(m_TurnAxis);
}

const float ACellphoneManager::openSpeed = 90.0f;
const float ACellphoneManager::maxOpenAngle = 160.0f;

// Called when the game starts or when spawned
void ACellphoneManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACellphoneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isOpening)
	{
		//ƒKƒ‰ƒP[‚ðŠJ‚¢‚½Žž‚Ìˆ—
		OpenCellphone(DeltaTime);
	}
}

// Called to bind functionality to input
void ACellphoneManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("OpenCellphone", IE_Pressed, this, &ACellphoneManager::SetIsOpening);
}

void ACellphoneManager::OpenCellphone(float deltaTime)
{
	if (m_openAngle > 0.0f)
	{
		m_openAngle -= openSpeed * deltaTime;
		m_TurnAxis->SetWorldRotation(FQuat(FRotator(m_openAngle, 0.0f, 0.0f)));
		
	}
}