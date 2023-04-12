// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"

#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/BlasterComponents/CombatComponent.h"


void AAmmoPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter)
	{
		OnOverlap(BlasterCharacter);
	}
}

void AAmmoPickup::OnOverlap(ABlasterCharacter* BlasterCharacter)
{
	if (BlasterCharacter && BlasterCharacter->GetCombat())
	{
		BlasterCharacter->GetCombat()->PickupAmmo(WeaponType, AmmoAmount);
	}

	Destroy();
}
