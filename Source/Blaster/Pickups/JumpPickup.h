// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Pickup.h"

#include "JumpPickup.generated.h"


UCLASS()
class BLASTER_API AJumpPickup : public APickup
{
	GENERATED_BODY()


public:


protected:

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlap(ABlasterCharacter* BlasterCharacter) override;


private:

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float JumpZVelocityBuff = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float JumpBuffTime = 30.f;
};
