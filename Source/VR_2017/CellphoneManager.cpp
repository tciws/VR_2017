// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_2017.h"
#include "CellphoneManager.h"


// Sets default values
ACellphoneManager::ACellphoneManager() : 
	m_openAngle(0.0f),
	m_isOpen(false)
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

// Called when the game starts or when spawned
void ACellphoneManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACellphoneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isOpen)
	{
		//ƒKƒ‰ƒP[ŠJ‚¢‚½Žž‚Ìˆ—
	}
}

// Called to bind functionality to input
void ACellphoneManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("OpenCellphoone", IE_Pressed, this, &ACellphoneManager::OpenCellphone);
}

void ACellphoneManager::OpenCellphone()
{
	m_isOpen = !m_isOpen;
}

