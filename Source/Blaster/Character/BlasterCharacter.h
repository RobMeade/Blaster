// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"

#include "Blaster/BlasterTypes/CombatState.h"
#include "Blaster/BlasterTypes/Team.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "Blaster/Interfaces/InteractWithCrosshairsInterface.h"

#include "BlasterCharacter.generated.h"


class UAnimMontage;
class UBoxComponent;
class UCameraComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USceneComponent;
class USoundCue;
class USpringArmComponent;
class UWidgetComponent;

class ABlasterGameMode;
class ABlasterPlayerController;
class ABlasterPlayerState;
class UBuffComponent;
class UCombatComponent;
class ULagCompensationComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftGame);


UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter, public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()


public:

	ABlasterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;

	/**
	 * Play montages
	 */
	void PlayFireMontage(bool bAiming);
	void PlayReloadMontage();
	void PlayEliminationMontage();
	void PlayThrowGrenadeMontage();
	void PlaySwapWeaponsMontage();

	virtual void Destroyed() override;
		
	//virtual void OnRep_PlayerState() override;

	void SetOverlappingWeapon(class AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();
	FORCEINLINE float GetAimOffsetYaw() const { return AimOffsetYaw; }
	FORCEINLINE float GetAimOffsetPitch() const { return AimOffsetPitch; }
	AWeapon* GetEquippedWeapon();
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }

	FVector GetHitTarget() const;

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }

	void Eliminated(bool bPlayerLeftGame);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastEliminated(bool bPlayerLeftGame);
	
	FORCEINLINE bool IsEliminated() const { return bEliminated; }

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetHealth(float Amount) { Health = Amount; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	FORCEINLINE float GetShield() const { return Shield; }
	FORCEINLINE void SetShield(float Amount) { Shield = Amount; }
	FORCEINLINE float GetMaxShield() const { return MaxShield; }

	void UpdateHUDHealth();
	void UpdateHUDShield();

	UPROPERTY()
	ABlasterPlayerState* BlasterPlayerState;

	ECombatState GetCombatState() const;

	UPROPERTY(Replicated)
	bool bDisableGameplay = false;

	FORCEINLINE UCombatComponent* GetCombat() const { return Combat; }
	FORCEINLINE bool GetDisableGameplay() const { return bDisableGameplay; }

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSniperScopeWidget(bool bShowScope);

	FORCEINLINE UAnimMontage* GetReloadMontage() const { return ReloadMontage; }

	FORCEINLINE UStaticMeshComponent* GetAttachedGrenade() const { return AttachedGrenade; }

	FORCEINLINE UBuffComponent* GetBuff() const { return Buff; }

	void SpawnDefaultWeapon();

	bool IsLocallyReloading();

	/*
	 * Hit boxes for server rewind
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Combat|Hit Boxes")
	TMap<FName, UBoxComponent*> HitBoxComponents;

	FORCEINLINE ULagCompensationComponent* GetLagCompensation() const { return LagCompensation; }

	bool bFinishedSwappingWeapons = false;
		
	UFUNCTION(Server, Reliable)
	void ServerLeaveGame();
	
	FOnLeftGame OnLeftGame;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastGainedTheLead();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLostTheLead();

	void SetTeamColor(ETeam Team);

	FORCEINLINE bool IsHoldingTheFlag() const;
	
	ETeam GetTeam();

	void SetHoldingTheFlag(bool bHolding);


protected:

	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void CrouchButtonPressed();
	void ReloadButtonPressed();
	void ThrowGrenadeButtonPressed();
	void EquipButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void CalculateAimOffsetPitch();
	void AimOffset(float DeltaTime);
	void SimProxiesTurn();
	virtual void Jump() override;
	virtual void OnRep_ReplicatedMovement() override;
	void FireButtonPressed();
	void FireButtonReleased();
	void PlayHitReactMontage();
	void SetSpawnPoint();
	void OnPlayerStateInitialized();

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	void InitialiseHUD();

	// Poll for any relevant classes and initialise our HUD
	void PollInit();
	void RotateInPlace(float DeltaTime);
	void DropOrDestroyWeapon(AWeapon* Weapon);
	void DropOrDestroyWeapons();


private:

	/*
	 * Blaster Components
	 */

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* Combat;

	UPROPERTY(VisibleAnywhere)
	ULagCompensationComponent* LagCompensation;

	UPROPERTY(VisibleAnywhere)
	UBuffComponent* Buff;


	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	// rpcs
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	float AimOffsetYaw;
	float AimOffsetYawInterp;
	float AimOffsetPitch;
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

	/*
	 * Animation Montages
	 */

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* FireWeaponMontage;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* EliminationMontage;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* ThrowGrenadeMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* SwapWeaponMontage;

	void HideCharacterIfCameraClose();

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	bool bRotateRootBone;
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplication;

	float CalculateSpeed();

	/*
	 * Player health
	 */

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health;

	UFUNCTION()
	void OnRep_Health(float LastHealth);

	/*
	 * Player shield
	 */

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxShield = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Shield, EditAnywhere, Category = "Player Stats")
	float Shield = 0.f;

	UFUNCTION()
	void OnRep_Shield(float LastShield);

	UPROPERTY()
	ABlasterPlayerController* BlasterPlayerController;

	bool bEliminated = false;

	FTimerHandle EliminatedTimer;

	UPROPERTY(EditDefaultsOnly)
	float EliminatedDelay = 3.f;

	void EliminatedTimerFinished();

	bool bLeftGame = false;

	/*
	 * Dissolve effect
	 */

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;

	FOnTimelineFloat DissolveTrack;

	UPROPERTY(EditAnywhere, Category = "Eliminated")
	UCurveFloat* DissolveCurve;

	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);

	void StartDissolve();

	// Dynamic instance that we can change at run time
	UPROPERTY(VisibleAnywhere, Category = "Eliminated")
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	// Material instance, set on the Blueprint, usedw ith the dynamic material instance
	UPROPERTY(VisibleAnywhere, Category = "Eliminated")
	UMaterialInstance* DissolveMaterialInstance;

	/**
	 * Team colors
	 */

	UPROPERTY(EditAnywhere, Category = "Eliminated|Teams")
	UMaterialInstance* RedTeamMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Eliminated|Teams")
	UMaterialInstance* RedTeamDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Eliminated|Teams")
	UMaterialInstance* BlueTeamMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Eliminated|Teams")
	UMaterialInstance* BlueTeamDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Eliminated|Teams")
	UMaterialInstance* NoTeamMaterialInstance;

	/*
	 * Elimination effects
	 */

	UPROPERTY(EditAnywhere)
	UParticleSystem* ElimBotEffect;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ElimBotComponent;

	UPROPERTY(EditAnywhere)
	USoundCue* ElimBotSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UNiagaraSystem* CrownSystem;

	UPROPERTY()
	UNiagaraComponent* CrownComponent;

	/*
	 * Grenade
	 */

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AttachedGrenade;

	/*
	 * Default Weapon
	 */

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AWeapon> DefaultWeaponClass;

	/*
	 * Hit boxes used for server side rewind
	 */

	void SetHitBoxBoneMappings();

	TMap<FName, FName> HitBoxBoneMappings;

	UPROPERTY()
	ABlasterGameMode* BlasterGameMode;
};
