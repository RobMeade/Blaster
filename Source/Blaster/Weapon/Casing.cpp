// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

#include "Materials/MaterialInterface.h"

ACasing::ACasing()
{
	PrimaryActorTick.bCanEverTick = false;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasingMesh"));
	SetRootComponent(CasingMesh);
	
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetNotifyRigidBodyCollision(true);
	CasingMesh->SetEnableGravity(true);

	ShellEjectionImpulse = 10.f;

	SelfDestructWaitTime = 10.f;


	MinCoolTime = 1.f;
	MaxCoolTime = 1.5f;
	CoolTime = FMath::RandRange(MinCoolTime, MaxCoolTime);
	CoolRate = 0.1f;
}

void ACasing::BeginPlay()
{
	Super::BeginPlay();

	CasingMesh->OnComponentHit.AddDynamic(this, &ACasing::OnHit);

	CasingMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);
	
	DynamicMaterialInstance = CasingMesh->CreateDynamicMaterialInstance(0);
	if(DynamicMaterialInstance)
	{
		GetWorld()->GetTimerManager().SetTimer(CoolTimerHandle, this, &ACasing::Cool, CoolRate, true);

		EmissivePower = DynamicMaterialInstance->K2_GetScalarParameterValue(FName("EmissivePower"));
		EmissivePowerDelta = (EmissivePower / CoolTime) * CoolRate;		
	}
}

void ACasing::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	CasingMesh->OnComponentHit.RemoveDynamic(this, &ACasing::OnHit);

	GetWorld()->GetTimerManager().SetTimer(SelfDestructTimerHandle, this, &ACasing::SelfDestruct, SelfDestructWaitTime);

	if(ShellSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
}

void ACasing::SelfDestruct()
{
	GetWorld()->GetTimerManager().ClearTimer(SelfDestructTimerHandle);
	Destroy();
}

void ACasing::Cool()
{
	if(DynamicMaterialInstance == nullptr) { return; }

	EmissivePower -= EmissivePowerDelta;
	DynamicMaterialInstance->SetScalarParameterValue(FName("EmissivePower"), EmissivePower);

	if(EmissivePower <= 0.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(CoolTimerHandle);
	}
}
