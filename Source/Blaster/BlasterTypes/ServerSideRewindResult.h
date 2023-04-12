// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ServerSideRewindResult.generated.h"


USTRUCT(BlueprintType)
struct FServerSideRewindResult
{
	GENERATED_BODY()


public:

	UPROPERTY()
	bool bHitConfirmed;

	UPROPERTY()
	bool bHeadShot;
};
