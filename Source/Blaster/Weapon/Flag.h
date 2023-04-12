// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"

#include "Flag.generated.h"


UCLASS()
class BLASTER_API AFlag : public AWeapon
{
	GENERATED_BODY()


public:

	AFlag();

	virtual void Dropped() override;
	void ResetFlag();

	FORCEINLINE FTransform GetInitialLocationAndRotation() const { return InitialLocationAndRotation; }


protected:

	virtual void OnWeaponEquipped() override;
	virtual void OnWeaponDropped() override;
	virtual void BeginPlay() override;


private:

	FTransform InitialLocationAndRotation;

};
