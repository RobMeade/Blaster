// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "CharacterOverlay.generated.h"


class UImage;
class UProgressBar;
class UTextBlock;
class UWidgetAnimation;


UCLASS()
class BLASTER_API UCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ShieldBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ShieldText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BlueTeamScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamScoreSpacer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RedTeamScore;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefeatsValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponAmmoValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CarriedAmmoValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EliminatedByText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchCountdownText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GrenadesValue;

	UPROPERTY(meta = (BindWidget))
	UImage* HighPingImage;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HighPingAnimation;


protected:


private:


};
