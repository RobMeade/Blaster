// Fill out your copyright notice in the Description page of Project Settings.


#include "EliminatedAnnouncement.h"

#include "Components/TextBlock.h"


void UEliminatedAnnouncement::SetEliminatedAnnouncementText(const FString& AttackerName, const FString& VictimName) const
{
	if (AnnouncementText)
	{
		const FString EliminatedAnnouncementText = FString::Printf(TEXT("%s eliminated %s!"), *AttackerName, *VictimName);
		AnnouncementText->SetText(FText::FromString(EliminatedAnnouncementText));
	}
}
