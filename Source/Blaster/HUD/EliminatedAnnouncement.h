// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "EliminatedAnnouncement.generated.h"


class UHorizontalBox;
class UTextBlock;


UCLASS()
class BLASTER_API UEliminatedAnnouncement : public UUserWidget
{
	GENERATED_BODY()


public:

	void SetEliminatedAnnouncementText(const FString& AttackerName, const FString& VictimName) const;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* AnnouncementBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AnnouncementText;


protected:


private:


};
