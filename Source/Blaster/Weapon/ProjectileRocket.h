// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Projectile.h"
#include "ProjectileRocket.generated.h"


class URocketMovementComponent;


UCLASS()
class BLASTER_API AProjectileRocket : public AProjectile
{
	GENERATED_BODY()


public:

	AProjectileRocket();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void Destroyed() override;


protected:

	virtual void BeginPlay() override;
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere, Category = "Projectile|SFX")
	USoundCue* FlightLoop;

	UPROPERTY()
	UAudioComponent* FlightLoopAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile|SFX")
	USoundAttenuation* FlightLoopAttenuation;

	UPROPERTY(VisibleAnywhere)
	URocketMovementComponent* RocketMovementComponent;


private:

	
};
