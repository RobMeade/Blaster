// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BlasterGameMode.generated.h"


namespace MatchState
{
	extern BLASTER_API const FName Cooldown;	// match duration has been reached, display winner, and begin cooldown timer
}


class ABlasterCharacter;
class ABlasterPlayerController;
class ABlasterPlayerState;


UCLASS()
class BLASTER_API ABlasterGameMode : public AGameMode
{
	GENERATED_BODY()


public:

	ABlasterGameMode();

	virtual void Tick(float DeltaTime) override;
	virtual void PlayerEliminated(ABlasterCharacter* EliminatedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController);
	virtual void RequestRespawn(ACharacter* EliminatedCharacter, AController* EliminatedController);
	void PlayerLeftGame(ABlasterPlayerState* LeavingPlayerState);

	virtual float CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage);

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 120.f;
	
	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;

	float LevelStartingTime = 0.f;

	FORCEINLINE float GetCountdownTime() const { return CountdownTime; }

	bool bTeamsMatch = false;


protected:

	virtual void BeginPlay() override;
	virtual void OnMatchStateSet() override;


private:

	AActor* GetSpawnPointWithLargestMinimumDistance(TArray<AActor*> PlayerStarts, TArray<AActor*> Players) const;
	float GetMinimumDistance(const AActor* PlayerStart, const TArray<AActor*> Players) const;
	
	float CountdownTime = 0.f;
};
