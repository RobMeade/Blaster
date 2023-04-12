// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"


class APlayerController;
class UTexture2D;
class UUserWidget;

class UAnnouncement;
class UCharacterOverlay;
class UEliminatedAnnouncement;


USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()


public:

	UTexture2D* CrosshairsCenter;
	UTexture2D* CrosshairsLeft;
	UTexture2D* CrosshairsRight;
	UTexture2D* CrosshairsTop;
	UTexture2D* CrosshairsBottom;
	float CrosshairsSpread;
	FLinearColor CrosshairsColor;
};


UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()


public:

	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "Blaster HUD")
	TSubclassOf<UUserWidget> CharacterOverlayClass;

	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;

	UPROPERTY(EditAnywhere, Category = "Blaster HUD|Announcements")
	TSubclassOf<UUserWidget> AnnouncementClass;

	UPROPERTY()
	UAnnouncement* Announcement;

	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }

	void AddCharacterOverlay();
	void AddAnnouncement();
	void AddEliminatedAnnouncement(const FString& AttackerName, const FString& VictimName);


protected:

	virtual void BeginPlay() override;


private:

	UPROPERTY()
	APlayerController* OwningPlayer;

	FHUDPackage HUDPackage;
	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairsColor);

	UPROPERTY(EditAnywhere, Category = "Blaster HUD|Crosshairs")
	float CrosshairsSpreadMax = 16.f;

	UPROPERTY(EditAnywhere, Category = "Blaster HUD|Announcements")
	TSubclassOf<UEliminatedAnnouncement> EliminatedAnnouncementClass;

	UPROPERTY(EditAnywhere, Category = "Blaster HUD|Announcements")
	float EliminatedAnnouncementDuration = 2.5f;

	UFUNCTION()
	void EliminatedAnnouncementTimerFinished(UEliminatedAnnouncement* AnnouncementToRemove);

	UPROPERTY()
	TArray<UEliminatedAnnouncement*> EliminationAnnouncementWidgets;
};
