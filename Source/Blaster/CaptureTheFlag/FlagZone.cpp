// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagZone.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Blaster/GameMode/CaptureTheFlagGameMode.h"
#include "Blaster/Weapon/Flag.h"


AFlagZone::AFlagZone()
{
	PrimaryActorTick.bCanEverTick = false;

	ZoneSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Zone Sphere"));
	SetRootComponent(ZoneSphere);
}

void AFlagZone::BeginPlay()
{
	Super::BeginPlay();

	ZoneSphere->OnComponentBeginOverlap.AddDynamic(this, &AFlagZone::OnSphereOverlap);
}

void AFlagZone::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFlag* OverlappingFlag = Cast<AFlag>(OtherActor);
	if (OverlappingFlag && OverlappingFlag->GetTeam() != Team)
	{
		OverlappingFlag->GetWeaponMesh()->SetSimulatePhysics(false);

		ACaptureTheFlagGameMode* GameMode = GetWorld()->GetAuthGameMode<ACaptureTheFlagGameMode>();
		if (GameMode && OverlappingFlag->GetOwner())
		{
			GameMode->FlagCaptured(OverlappingFlag, this);
		}

		OverlappingFlag->ResetFlag();
	}
}
