// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"

#include "Blaster/Weapon/Weapon.h"

#include "AmmoPickup.generated.h"


UCLASS()
class BLASTER_API AAmmoPickup : public APickup
{
	GENERATED_BODY()


public:


protected:

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlap(ABlasterCharacter* BlasterCharacter) override;


private:

	UPROPERTY(EditAnywhere, Category = "Pickup")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	int32 AmmoAmount = 30;
};
