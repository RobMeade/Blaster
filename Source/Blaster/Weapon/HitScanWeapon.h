// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Weapon.h"

#include "HitScanWeapon.generated.h"


class UParticleSystem;


UCLASS()
class BLASTER_API AHitScanWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	virtual void Fire(const FVector& HitTarget) override;


protected:

	UPROPERTY(EditAnywhere, Category = "Weapon|VFX")
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, Category = "Weapon|SFX")
	USoundCue* HitSound;

	void WeaponTraceHit(const FVector& TraceStart, const FVector& HitTarget, FHitResult& OutHit);


private:

	UPROPERTY(EditAnywhere, Category = "Weapon|VFX")
	UParticleSystem* BeamParticles;

	UPROPERTY(EditAnywhere, Category = "Weapon|VFX")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Weapon|SFX")
	USoundCue* FireSound;
};
