// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPickup.h"

#include "Blaster/BlasterComponents/BuffComponent.h"
#include "Blaster/Character/BlasterCharacter.h"


void AJumpPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter)
	{
		OnOverlap(BlasterCharacter);
	}
}

void AJumpPickup::OnOverlap(ABlasterCharacter* BlasterCharacter)
{
	if (BlasterCharacter && BlasterCharacter->GetBuff())
	{
		BlasterCharacter->GetBuff()->BuffJump(JumpZVelocityBuff, JumpBuffTime);
	}

	Destroy();
}
