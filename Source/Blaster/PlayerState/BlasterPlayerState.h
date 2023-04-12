// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "Blaster/BlasterTypes/DefeatPackage.h"
#include "Blaster/BlasterTypes/Team.h"

#include "BlasterPlayerState.generated.h"


class ABlasterCharacter;
class ABlasterPlayerController;


UCLASS()
class BLASTER_API ABlasterPlayerState : public APlayerState
{
	GENERATED_BODY()


public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_Score() override;

	//UFUNCTION()
	//virtual void OnRep_Defeats();

	UFUNCTION()
	virtual void OnRep_Defeated();

	void AddToScore(float ScoreValue);
	//void AddToDefeats(int32 DefeatsValue);

	void Defeated(int32 DefeatValue, FString AttackerName);

	//void DisplayEliminatedBy(bool DisplayEliminatedBy, FString AttackerName = "");

	FORCEINLINE FDefeatPackage GetDefeatPackage() { return DefeatPackage; }

	FORCEINLINE ETeam GetTeam() const { return Team; }
	void SetTeam(const ETeam TeamToSet);


protected:


private:

	UPROPERTY()
	ABlasterCharacter* Character;

	UPROPERTY()
	ABlasterPlayerController* Controller;

	//UPROPERTY(ReplicatedUsing = OnRep_Defeats)
	//int32 Defeats;


	UPROPERTY(ReplicatedUsing = OnRep_Defeated)
	FDefeatPackage DefeatPackage;

	UPROPERTY(ReplicatedUsing = OnRep_Team)
	ETeam Team = ETeam::ET_NoTeam;

	UFUNCTION()
	void OnRep_Team();
};
