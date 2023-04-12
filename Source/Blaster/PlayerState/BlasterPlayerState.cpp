// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterPlayerState.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Net/UnrealNetwork.h"


void ABlasterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ABlasterPlayerState, Defeats);
	DOREPLIFETIME(ABlasterPlayerState, DefeatPackage);
	DOREPLIFETIME(ABlasterPlayerState, Team);
}

void ABlasterPlayerState::AddToScore(float ScoreValue)
{
	SetScore(GetScore() + ScoreValue);

	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}

void ABlasterPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());			
		}
	}
}

//void ABlasterPlayerState::AddToDefeats(int32 DefeatsValue)
//{
//	Defeats += DefeatsValue;
//
//	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
//	if (Character)
//	{
//		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
//		if (Controller)
//		{
//			Controller->SetHUDDefeats(Defeats);
//		}
//	}
//}

//void ABlasterPlayerState::OnRep_Defeats()
//{
//	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
//	if (Character)
//	{
//		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
//		if (Controller)
//		{
//			Controller->SetHUDDefeats(Defeats);
//		}
//	}
//}

void ABlasterPlayerState::Defeated(int32 DefeatValue, FString AttackerName)
{
	FDefeatPackage TempDefeatPackage;
	TempDefeatPackage.DefeatValue = DefeatPackage.DefeatValue + DefeatValue;
	TempDefeatPackage.DefeatedByName = AttackerName;

	DefeatPackage = TempDefeatPackage;

	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			if (DefeatPackage.DefeatValue > 0)
			{
				Controller->SetHUDDefeated(false, DefeatPackage);
			}
			else
			{
				Controller->SetHUDDefeated(true);
			}
		}
	}
}

void ABlasterPlayerState::OnRep_Defeated()
{
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			if (DefeatPackage.DefeatValue > 0)
			{
				Controller->SetHUDDefeated(false, DefeatPackage);
			}
			else
			{
				Controller->SetHUDDefeated(true);
			}
		}
	}
}

void ABlasterPlayerState::SetTeam(const ETeam TeamToSet)
{
	Team = TeamToSet;

	ABlasterCharacter* BCharacter = Cast<ABlasterCharacter>(GetPawn());
	if (BCharacter)
	{
		BCharacter->SetTeamColor(Team);
	}
}

void ABlasterPlayerState::OnRep_Team()
{
	ABlasterCharacter* BCharacter = Cast<ABlasterCharacter>(GetPawn());
	if (BCharacter)
	{
		BCharacter->SetTeamColor(Team);
	}
}

//void ABlasterPlayerState::DisplayEliminatedBy(bool DisplayEliminatedBy, FString AttackerName)
//{
//	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
//	if (Character)
//	{
//		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
//		if (Controller)
//		{
//			Controller->SetHUDEliminatedBy(DisplayEliminatedBy, AttackerName);
//		}
//	}
//}
