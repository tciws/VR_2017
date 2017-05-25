// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "UsableActor.h"
#include "DoorActor.generated.h"

UCLASS()
class VR_2017_API ADoorActor : public AUsableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual ItemName Event() override;

	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	USceneComponent* m_Parent;

	UPROPERTY(EditAnywhere)
		UShapeComponent* m_TurnAxis;

	UPROPERTY(EditAnywhere)
		UShapeComponent* m_BoxTrigger;

	static const float openSpeed;
	static const float maxOpenAngle;

	UPROPERTY(EditAnywhere)
	bool m_isOpen;

	void OpenDoor(float deltaTime);

	void CloseDoor(float deltaTime);

	float doorAngle;
};
