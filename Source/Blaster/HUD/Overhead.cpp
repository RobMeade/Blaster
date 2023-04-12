// Fill out your copyright notice in the Description page of Project Settings.


#include "Overhead.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"


void UOverhead::SetDisplayText(FString TextToDisplay)
{
	if(DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverhead::ShowPlayerNetRole(APawn* InPawn)
{
	//if(InPawn == nullptr)
	//{
	//	return;
	//}

	ENetRole Role = InPawn->GetLocalRole();
	FString RoleString;

	switch(Role)
	{
	case ENetRole::ROLE_Authority:
		RoleString = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		RoleString = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		RoleString = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		RoleString = FString("None");
		break;
	}

	//FString PlayerName;

	//APlayerState* PlayerState = InPawn->GetPlayerState();
	//if(PlayerState)
	//{
	//	PlayerName = PlayerState->GetPlayerName();
	//}
	//else
	//{
	//	PlayerName = "Unknown - No PlayerState";
	//}

	//FString RemoteRoleString = FString::Printf(TEXT("Role: %s - %s"), *RoleString, *PlayerName);
	FString RemoteRoleString = FString::Printf(TEXT("Role: %s"), *RoleString);
	SetDisplayText(RemoteRoleString);
}

void UOverhead::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromParent();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

}
