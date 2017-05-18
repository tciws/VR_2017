// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CellphoneManager.generated.h"

UCLASS()
class VR_2017_API ACellphoneManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACellphoneManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OpenCellphone();
	
private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_TurnAxis;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_TopBodyMesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_UnderBodyMesh;

	float m_openAngle;

	bool m_isOpen;
	
};
