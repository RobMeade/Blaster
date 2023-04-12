// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterHUD.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "GameFramework/PlayerController.h"

#include "Announcement.h"
#include "CharacterOverlay.h"
#include "EliminatedAnnouncement.h"


void ABlasterHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ViewportSize;
	if(GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2D ViewportCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);

		float SpreadScaled = CrosshairsSpreadMax * HUDPackage.CrosshairsSpread;

		if(HUDPackage.CrosshairsCenter)
		{
			FVector2D Spread(0.f, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsCenter, ViewportCenter, Spread, HUDPackage.CrosshairsColor);
		}
		if(HUDPackage.CrosshairsLeft)
		{
			FVector2D Spread(-SpreadScaled, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsLeft, ViewportCenter, Spread, HUDPackage.CrosshairsColor);
		}
		if(HUDPackage.CrosshairsRight)
		{
			FVector2D Spread(SpreadScaled, 0.f);
			DrawCrosshair(HUDPackage.CrosshairsRight, ViewportCenter, Spread, HUDPackage.CrosshairsColor);
		}
		if(HUDPackage.CrosshairsTop)
		{
			FVector2D Spread( 0.f, -SpreadScaled);
			DrawCrosshair(HUDPackage.CrosshairsTop, ViewportCenter, Spread, HUDPackage.CrosshairsColor);
		}
		if(HUDPackage.CrosshairsBottom)
		{
			FVector2D Spread( 0.f, SpreadScaled);
			DrawCrosshair(HUDPackage.CrosshairsBottom, ViewportCenter, Spread, HUDPackage.CrosshairsColor);
		}
	}
}

void ABlasterHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ABlasterHUD::AddCharacterOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if(PlayerController && CharacterOverlayClass)
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
		CharacterOverlay->AddToViewport();
	}
}

void ABlasterHUD::AddAnnouncement()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if(PlayerController && AnnouncementClass && Announcement == nullptr)
	{
		Announcement = CreateWidget<UAnnouncement>(PlayerController, AnnouncementClass);
		Announcement->AddToViewport();
	}
}

void ABlasterHUD::AddEliminatedAnnouncement(const FString& AttackerName, const FString& VictimName)
{
	OwningPlayer = OwningPlayer == nullptr ? GetOwningPlayerController() : OwningPlayer;

	if (OwningPlayer && EliminatedAnnouncementClass)
	{
		UEliminatedAnnouncement* EliminatedAnnouncement = CreateWidget<UEliminatedAnnouncement>(OwningPlayer, EliminatedAnnouncementClass);
		if (EliminatedAnnouncement)
		{
			EliminatedAnnouncement->SetEliminatedAnnouncementText(AttackerName, VictimName);
			EliminatedAnnouncement->AddToViewport();

			for (UEliminatedAnnouncement* AnnouncementWidget : EliminationAnnouncementWidgets)
			{
				if (AnnouncementWidget && AnnouncementWidget->AnnouncementBox)
				{
					UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(AnnouncementWidget->AnnouncementBox);
					if (CanvasPanelSlot)
					{
						FVector2D Position = CanvasPanelSlot->GetPosition();
						FVector2D NewPosition(CanvasPanelSlot->GetPosition().X, Position.Y - CanvasPanelSlot->GetSize().Y);

						CanvasPanelSlot->SetPosition(NewPosition);
					}
				}
			}
			
			EliminationAnnouncementWidgets.Add(EliminatedAnnouncement);

			FTimerHandle EliminatedAnnouncementTimerHandle;
			FTimerDelegate EliminatedAnnouncementDelegate;
			EliminatedAnnouncementDelegate.BindUFunction(this, FName("EliminatedAnnouncementTimerFinished"), EliminatedAnnouncement);
			GetWorldTimerManager().SetTimer(EliminatedAnnouncementTimerHandle, EliminatedAnnouncementDelegate, EliminatedAnnouncementDuration, false);
		}
	}
}

void ABlasterHUD::EliminatedAnnouncementTimerFinished(UEliminatedAnnouncement* AnnouncementToRemove)
{
	if (AnnouncementToRemove)
	{
		AnnouncementToRemove->RemoveFromParent();
	}
}

void ABlasterHUD::DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairsColor)
{
	const float TextureWidth = Texture->GetSizeX();
	const float TextureHeight = Texture->GetSizeY();
	const FVector2D TextureDrawPoint(ViewportCenter.X - (TextureWidth / 2.f) + Spread.X, ViewportCenter.Y - (TextureHeight / 2.f) + Spread.Y);

	DrawTexture(Texture, TextureDrawPoint.X, TextureDrawPoint.Y, TextureWidth, TextureHeight, 0.f, 0.f, 1.f, 1.f, CrosshairsColor);
}
