// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blaster/BlasterTypes/HitBoxInformation.h"

#include "FramePackage.generated.h"


USTRUCT(BlueprintType)
struct FFramePackage
{
	GENERATED_BODY()


public:

	UPROPERTY()
	float Time;

	UPROPERTY()
	TMap<FName, FHitBoxInformation> HitBoxInfo;

	UPROPERTY()
	ABlasterCharacter* Character = nullptr;
};