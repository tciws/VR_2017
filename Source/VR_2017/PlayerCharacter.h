// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class VR_2017_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveForward(float value);

	virtual void MoveRight(float value);

	void OpenDoor();

	bool GetIsOpeningDoor()
	{
		return m_isOpeningDoor;
	}

	class AUsableActor* GetUsableInView();

private:
	UPROPERTY(EditAnywhere)
		float maxTraceDistance;

	UCameraComponent* FirstPersonCamera;

	bool m_isOpeningDoor;
};
