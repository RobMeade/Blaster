// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DefeatPackage.generated.h"


USTRUCT()
struct FDefeatPackage
{
	GENERATED_BODY()


public:

	FDefeatPackage()
	{
		DefeatValue = 0;
		DefeatedByName = "";
	}

	UPROPERTY()
	int32 DefeatValue;

	UPROPERTY()
	FString DefeatedByName;
};
