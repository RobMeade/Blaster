// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"

#include "MultiplayerSessionsSubsystem.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UMultiplayerSessionsSubsystem* SubSystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
		check (SubSystem);

		if(NumberOfPlayers == SubSystem->DesiredNumbPublicConnections)
		{
			UWorld* World = GetWorld();
			if(World)
			{
				bUseSeamlessTravel = true;

				FString MatchType = SubSystem->DesiredMatchType;

				if (MatchType == "DeathMatch")
				{
					World->ServerTravel(FString("/Game/Blaster/Maps/DeathMatch?listen"));					
				}
				else if (MatchType == "TeamDeathMatch")
				{
					World->ServerTravel(FString("/Game/Blaster/Maps/TeamsDeathMatch?listen"));						
				}
				else if (MatchType == "CaptureTheFlag")
				{
					World->ServerTravel(FString("/Game/Blaster/Maps/CaptureTheFlag?listen"));						
				}
			}
		}
	}
}
