// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PickupSpawnPoint.generated.h"


class APickup;


UCLASS()
class BLASTER_API APickupSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	

	APickupSpawnPoint();

	virtual void Tick(float DeltaTime) override;


protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<TSubclassOf<APickup>> PickupClasses;

	UPROPERTY()
	APickup* SpawnedPickup;

	void SpawnPickup();

	UFUNCTION()
	void StartSpawnPickupTimer(AActor* DestroyedActor);	// parameter added so that it can be bound to OnDestroyed
	void SpawnPickupTimerFinished();


private:
	
	FTimerHandle SpawnPickupTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MinimumSpawnPickupTime;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MaximumSpawnPickupTime;

};
