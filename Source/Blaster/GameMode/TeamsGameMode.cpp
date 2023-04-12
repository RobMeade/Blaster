// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamsGameMode.h"

#include "Engine/PlayerStartPIE.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

#include "Blaster/BlasterTypes/Team.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/GameState/BlasterGameState.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Blaster/PlayerStart/TeamPlayerStart.h"
#include "Blaster/PlayerState/BlasterPlayerState.h"


ATeamsGameMode::ATeamsGameMode()
{
	bTeamsMatch = true;
}

void ATeamsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//ABlasterGameState* BGameState = Cast<ABlasterGameState>(UGameplayStatics::GetGameState(this));
	//if (BGameState)
	//{
	//	ABlasterPlayerState* BPState = NewPlayer->GetPlayerState<ABlasterPlayerState>();
	//	if (BPState && BPState->GetTeam() == ETeam::ET_NoTeam)
	//	{
	//		if (BGameState->BlueTeam.Num() >= BGameState->RedTeam.Num())
	//		{
	//			BGameState->RedTeam.AddUnique(BPState);
	//			BPState->SetTeam(ETeam::ET_RedTeam);
	//		}
	//		else
	//		{
	//			BGameState->BlueTeam.AddUnique(BPState);
	//			BPState->SetTeam(ETeam::ET_BlueTeam);
	//		}
	//	}
	//}
}

void ATeamsGameMode::Logout(AController* Exiting)
{
	ABlasterGameState* BGameState = Cast<ABlasterGameState>(UGameplayStatics::GetGameState(this));
	ABlasterPlayerState* BPState = Exiting->GetPlayerState<ABlasterPlayerState>();
	if (BGameState && BPState)
	{
		if (BGameState->RedTeam.Contains(BPState))
		{
			BGameState->RedTeam.Remove(BPState);
		}
		if (BGameState->BlueTeam.Contains(BPState))
		{
			BGameState->BlueTeam.Remove(BPState);
		}
	}
}

void ATeamsGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	ABlasterGameState* BGameState = Cast<ABlasterGameState>(UGameplayStatics::GetGameState(this));
	if (BGameState)
	{
		for (auto PState : BGameState->PlayerArray)
		{
			ABlasterPlayerState* BPState = Cast<ABlasterPlayerState>(PState.Get());
			if (BPState && BPState->GetTeam() == ETeam::ET_NoTeam)
			{
				if (BGameState->BlueTeam.Num() >= BGameState->RedTeam.Num())
				{
					BGameState->RedTeam.AddUnique(BPState);
					BPState->SetTeam(ETeam::ET_RedTeam);
				}
				else
				{
					BGameState->BlueTeam.AddUnique(BPState);
					BPState->SetTeam(ETeam::ET_BlueTeam);
				}
			}
		}
	}
}

float ATeamsGameMode::CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage)
{
	if (Attacker == nullptr || Victim == nullptr)
	{
		return 0.f;
	}

	const ABlasterPlayerState* AttackerPState = Attacker->GetPlayerState<ABlasterPlayerState>();
	const ABlasterPlayerState* VictimPState = Victim->GetPlayerState<ABlasterPlayerState>();

	if (AttackerPState == nullptr || VictimPState == nullptr)
	{
		return BaseDamage;
	}

	if (AttackerPState == VictimPState)
	{
		return BaseDamage;
	}

	if (AttackerPState->GetTeam() == VictimPState->GetTeam())
	{
		return 0.f;
	}

	return BaseDamage;
}

void ATeamsGameMode::PlayerEliminated(ABlasterCharacter* EliminatedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	Super::PlayerEliminated(EliminatedCharacter, VictimController, AttackerController);

	ABlasterGameState* BGameState = Cast<ABlasterGameState>(UGameplayStatics::GetGameState(this));
	ABlasterPlayerState* AttackerPlayerState = AttackerController ? Cast<ABlasterPlayerState>(AttackerController->PlayerState) : nullptr;
	ABlasterPlayerState* VictimPlayerState = VictimController ? Cast<ABlasterPlayerState>(VictimController->PlayerState) : nullptr;

	// suicide is defined as a player being killed by their own grenade, grenade launcher, or rocket launcher

	//// awards points to own team for suicide
	//if (BGameState && AttackerPlayerState)
	//{
	//	if (AttackerPlayerState->GetTeam() == ETeam::ET_BlueTeam)
	//	{
	//		BGameState->BlueTeamScores();
	//	}

	//	if (AttackerPlayerState->GetTeam() == ETeam::ET_RedTeam)
	//	{
	//		BGameState->RedTeamScores();
	//	}
	//}

	//// awards no points for player suicide
	//if (BGameState && AttackerPlayerState && VictimPlayerState && AttackerPlayerState != VictimPlayerState)
	//{
	//	if (AttackerPlayerState->GetTeam() == ETeam::ET_BlueTeam)
	//	{
	//		BGameState->BlueTeamScores();
	//	}

	//	if (AttackerPlayerState->GetTeam() == ETeam::ET_RedTeam)
	//	{
	//		BGameState->RedTeamScores();
	//	}
	//}

	//// awards point to opposing team for player suicide
	//if (BGameState && AttackerPlayerState && VictimPlayerState)
	//{
	//	if (AttackerPlayerState->GetTeam() == ETeam::ET_BlueTeam)
	//	{
	//		if (AttackerPlayerState != VictimPlayerState)
	//		{
	//			BGameState->BlueTeamScores();				
	//		}
	//		else
	//		{
	//			BGameState->RedTeamScores();
	//		}
	//	}

	//	if (AttackerPlayerState->GetTeam() == ETeam::ET_RedTeam)
	//	{
	//		if (AttackerPlayerState != VictimPlayerState)
	//		{
	//			BGameState->RedTeamScores();				
	//		}
	//		else
	//		{
	//			BGameState->BlueTeamScores();
	//		}
	//	}
	//}

	// team loses point for player suicide
	if (BGameState && AttackerPlayerState && VictimPlayerState)
	{
		bool bIsSuicide = AttackerPlayerState == VictimPlayerState;

		if (AttackerPlayerState->GetTeam() == ETeam::ET_BlueTeam)
		{
			if (!bIsSuicide)
			{
				BGameState->BlueTeamScores();				
			}
			else
			{
				BGameState->BlueTeamLosesPoint();
			}
		}

		if (AttackerPlayerState->GetTeam() == ETeam::ET_RedTeam)
		{
			if (!bIsSuicide)
			{
				BGameState->RedTeamScores();				
			}
			else
			{
				BGameState->RedTeamLosesPoint();
			}
		}
	}
}

AActor* ATeamsGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	ABlasterGameState* BlasterGameState = Cast<ABlasterGameState>(UGameplayStatics::GetGameState(this));
	ABlasterPlayerState* BlasterPlayerState = Player->GetPlayerState<ABlasterPlayerState>();
	if (!BlasterGameState || !BlasterPlayerState)
	{
		return nullptr;		
	}
 
	// Attach player to a team.
	if (BlasterPlayerState->GetTeam() == ETeam::ET_NoTeam)
	{
		if (BlasterGameState->BlueTeam.Num() >= BlasterGameState->RedTeam.Num())
		{
			BlasterGameState->RedTeam.AddUnique(BlasterPlayerState);
			BlasterPlayerState->SetTeam(ETeam::ET_RedTeam);
		}
		else
		{
			BlasterGameState->BlueTeam.AddUnique(BlasterPlayerState);
			BlasterPlayerState->SetTeam(ETeam::ET_BlueTeam);
		}
	}
 
	// Choose a player start.
	const APawn* PawnToFit = ABlasterCharacter::StaticClass()->GetDefaultObject<APawn>();
	TArray<APlayerStart*> UnOccupiedStartPoints;
	UWorld* World = GetWorld();
	for (TActorIterator<ATeamPlayerStart> It(World); It; ++It)
	{
		ATeamPlayerStart* PlayerStart = *It;
 
		if (PlayerStart->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
			return PlayerStart;
		}
 
		const FVector ActorLocation = PlayerStart->GetActorLocation();
		const FRotator ActorRotation = PlayerStart->GetActorRotation();
		if (!World->EncroachingBlockingGeometry(PawnToFit, ActorLocation, ActorRotation) && PlayerStart->Team == BlasterPlayerState->GetTeam())
		{
			UnOccupiedStartPoints.Add(PlayerStart);
		}
	}
 
	if (UnOccupiedStartPoints.Num() > 0)
	{
		return UnOccupiedStartPoints[FMath::RandRange(0, UnOccupiedStartPoints.Num() - 1)];		
	}
 
	return nullptr;
}
