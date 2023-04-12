// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casing.generated.h"


UCLASS()
class BLASTER_API ACasing : public AActor
{
	GENERATED_BODY()


public:	

	ACasing();


protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CasingMesh;

	UPROPERTY(EditAnywhere)
	float ShellEjectionImpulse;

	UPROPERTY(EditAnywhere)
	class USoundCue* ShellSound;

	UPROPERTY(EditAnywhere)
	float MinCoolTime;

	UPROPERTY(EditAnywhere)
	float MaxCoolTime;

	UPROPERTY(EditAnywhere)
	float SelfDestructWaitTime;

	UFUNCTION()
	void SelfDestruct();

	UFUNCTION()
	void Cool();

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterialInstance;
	
	float CoolTime;
	float EmissivePower;
	float EmissivePowerDelta;
	float CoolRate;

	FTimerHandle SelfDestructTimerHandle;
	FTimerHandle CoolTimerHandle;
};
