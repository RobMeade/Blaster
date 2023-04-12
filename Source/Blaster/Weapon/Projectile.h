// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Projectile.generated.h"


class UBoxComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;
class USoundCue;


UCLASS()
class BLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()


public:

	AProjectile();

	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	/*
	 * Used with server side rewind
	 */

	bool bUseServerSideRewind = false;
	FVector_NetQuantize TraceStart;
	FVector_NetQuantize100 InitialVelocity;

	UPROPERTY(EditAnywhere)
	float InitialSpeed = 15000.f;


	// Only set this for Grenades and Rockets
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 20.f;

	// Doesn't matter for Grenades and Rockets
	UPROPERTY(EditAnywhere, Category = "Combat")
	float HeadShotDamage = 40.f;


protected:

	virtual void BeginPlay() override;
	void StartDestroyTimer();
	void DestroyTimerFinished();
	void SpawnTrailSystem();
	void ExplodeDamage();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Projectile|Damage")
	float MinimumDamage = 0.f;

	UPROPERTY(EditAnywhere, Category = "Projectile|Damage")
	float DamageFalloff = 1.f;

	UPROPERTY(EditAnywhere, Category = "Projectile|Damage")
	float DamageInnerRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = "Projectile|Damage")
	float DamageOuterRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "Projectile|VFX")
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, Category = "Projectile|VFX")
	USoundCue* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Projectile|VFX")
	UNiagaraSystem* TrailSystem;

	UPROPERTY()
	UNiagaraComponent* TrailSystemComponent;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	FTimerHandle DestroyTimerHandle;


private:

	UPROPERTY(EditAnywhere, Category = "Projectile|VFX")
	UParticleSystem* Tracer;

	UPROPERTY()
	UParticleSystemComponent* TracerComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float DestroyTime = 3.f;
};
