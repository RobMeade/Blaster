// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ServerSideRewindShotgunResult.generated.h"


USTRUCT(BlueprintType)
struct FServerSideRewindShotgunResult
{
	GENERATED_BODY()


public:

	UPROPERTY()
	TMap<ABlasterCharacter*, uint32> HeadShots;

	UPROPERTY()
	TMap<ABlasterCharacter*, uint32> BodyShots;
};
