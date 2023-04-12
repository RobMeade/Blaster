// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Pickup.generated.h"


class ABlasterCharacter;
class UNiagaraComponent;
class UNiagaraSystem;
class USoundCue;
class USphereComponent;


UCLASS()
class BLASTER_API APickup : public AActor
{
	GENERATED_BODY()

	
public:	

	APickup();

	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnOverlap(ABlasterCharacter* BlasterCharacter);

	UPROPERTY(EditAnywhere, Category = "Pickup|VFX")
	float BaseTurnRate = 45.f;


private:

	UPROPERTY(EditAnywhere)
	USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, Category = "Pickup|SFX")
	USoundCue* PickupSound;

	UPROPERTY(VisibleAnywhere, Category = "Pickup|VFX")
	UNiagaraComponent* PickupEffectComponent;

	UPROPERTY(EditAnywhere, Category = "Pickup|VFX")
	UNiagaraSystem* PickupEffect;

	FTimerHandle BindOverlapTimerHandle;

	float BindOverlapTime = 0.25f;

	void BindOverlapTimerFinished();

	AActor* GetClosestPlayerToPickup(const TArray<AActor*> Players) const;
};
