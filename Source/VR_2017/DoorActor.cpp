// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_2017.h"
#include "DoorActor.h"
#include "PlayerCharacter.h"


// Sets default values
ADoorActor::ADoorActor() :
	m_isOpen(false),
	doorAngle(0.0f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Parent = CreateDefaultSubobject<USceneComponent>(TEXT("Parent"));
	m_Parent->AttachTo(GetRootComponent());

	m_BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	m_BoxTrigger->bGenerateOverlapEvents = true;
	m_BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::TriggerEnter);
	m_BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ADoorActor::TriggerExit);
	m_BoxTrigger->AttachTo(m_Parent);

	m_TurnAxis = CreateDefaultSubobject<UBoxComponent>(TEXT("TurnAxis"));
	m_TurnAxis->AttachTo(m_Parent);

	m_MyMesh->AttachTo(m_TurnAxis);
}

// Edit turn parameter here.
const float ADoorActor::openSpeed = 90.0f;
const float ADoorActor::maxOpenAngle = 90.0f;

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isOpen)
	{
		OpenDoor(DeltaTime);
	}
	else
	{
		CloseDoor(DeltaTime);
	}
}

ItemName ADoorActor::Event()
{
	m_isOpen = true;
	return ItemName::noItem;
}

void ADoorActor::TriggerEnter(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//m_isOpen = true;
	//openDirection = 1.0f;
}

void ADoorActor::TriggerExit(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	m_isOpen = false;
	//GEngine->AddOnScreenDebugMessage(0, 15.f, FColor::Black, TEXT("close"));
}

void ADoorActor::OpenDoor(float deltaTime)
{
	if (doorAngle < maxOpenAngle)
	{
		doorAngle += openSpeed * deltaTime;
		m_TurnAxis->SetRelativeRotation(FQuat(FRotator(0.0f, doorAngle, 0.0f)));
	}
}

void ADoorActor::CloseDoor(float deltaTime)
{
	if (doorAngle > 0.0f)
	{
		doorAngle -= openSpeed * deltaTime;
		m_TurnAxis->SetRelativeRotation(FQuat(FRotator(0.0f, doorAngle, 0.0f)));
	}
}
