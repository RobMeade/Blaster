// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HitBoxInformation.generated.h"


USTRUCT(BlueprintType)
struct FHitBoxInformation
{
	GENERATED_BODY()


public:

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	FVector BoxExtent;
};