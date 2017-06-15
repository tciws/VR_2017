// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_2017.h"
#include "unordered_map"
#include "UsableActor.h"


// Sets default values
AUsableActor::AUsableActor():
	m_itemName(ItemName::noItem)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	m_MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
}

// Called when the game starts or when spawned
void AUsableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUsableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ItemName AUsableActor::Event()
{
	/****************** For Debug ***************************************/

	std::unordered_map<ItemName, FString> myMap{
		{ItemName::book, "book"},
		{ItemName::key, "key"},
		{ItemName::paper, "paper"},
		{ItemName::clip, "clip"},
		{ItemName::chair, "chair"}
	};

	FString item = "You got " + myMap.at(m_itemName);

	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, item);

	/*********************************************************************/

	// disable an actor
	//SetActorHiddenInGame(true);
	//SetActorEnableCollision(false);
	//SetActorTickEnabled(false);

	return m_itemName;
}

