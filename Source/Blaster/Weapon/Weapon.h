// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WeaponTypes.h"
#include "Blaster/BlasterTypes/Team.h"

#include "Weapon.generated.h"


class USoundCue;
class USphereComponent;
class UWidgetComponent;
class UTexture2D;
class ABlasterCharacter;
class ABlasterPlayerController;


UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_EquippedSecondary UMETA(DisplayName = "EquippedSecondary"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),

	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EFireType : uint8
{
	EFT_HitScan UMETA(DisplayName = "Hit Scan Weapon"),
	EFT_Projectile UMETA(DisplayName = "Projectile Weapon"),
	EFT_Shotgun UMETA(DisplayName = "Shotgun Weapon"),

	EFT_MAX UMETA(DisplayName = "DefaultMAX")
};


UCLASS()
class BLASTER_API AWeapon : public AActor
{
	GENERATED_BODY()


public:	

	AWeapon();

	virtual void Tick(float DeltaTime) override;
	void ShowPickupWidget(bool bShowWidget);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_Owner() override;
	void SetWeaponState(EWeaponState State);
	virtual void Fire(const FVector& HitTarget);
	virtual void Dropped();
	void AddAmmo(int32 AmmoToAdd);
	FVector TraceEndWithScatter(const FVector& HitTarget);

	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	FORCEINLINE float GetZoomedFOV() const { return ZoomedFOV; }
	FORCEINLINE float GetZoomInterpSpeed() const { return ZoomInterpSpeed; }
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE int32 GetAmmo() const { return Ammo; }
	FORCEINLINE int32 GetMagCapacity() const { return MagCapacity; }
	FORCEINLINE FString GetWeaponName() const { return WeaponName; }


	void SetWeaponNameFromType();
	
	/*
	 * Textures for the weapon crosshairs
	 */
	UPROPERTY(EditAnywhere, Category = "Weapon|UI|Crosshairs")
	UTexture2D* CrosshairsCenter;

	UPROPERTY(EditAnywhere, Category = "Weapon|UI|Crosshairs")
	UTexture2D* CrosshairsLeft;

	UPROPERTY(EditAnywhere, Category = "Weapon|UI|Crosshairs")
	UTexture2D* CrosshairsRight;

	UPROPERTY(EditAnywhere, Category = "Weapon|UI|Crosshairs")
	UTexture2D* CrosshairsTop;
	
	UPROPERTY(EditAnywhere, Category = "Weapon|UI|Crosshairs")
	UTexture2D* CrosshairsBottom;

	/*
	 * Automatic fire
	 */
	UPROPERTY(EditAnywhere, Category = "Weapon|Combat")
	float FireDelay = 0.15f;

	UPROPERTY(EditAnywhere, Category = "Weapon|Combat")
	bool bAutomatic = true;

	/*
	 * Ammo
	 */
	void SetHUDAmmo();
	bool IsEmpty();
	bool IsFull();

	/*
	 * Sound effects
	 */
	UPROPERTY(EditAnywhere, Category = "Weapon|SFX")
	USoundCue* EquipSound;

	/*
	 * Enabled or disable custom depth
	 */
	void EnableCustomDepth(bool bEnable);
	bool bDestroyWeapon = false;

	UPROPERTY(EditAnywhere)
	EFireType FireType;

	UPROPERTY(EditAnywhere, Category = "WEAPON|Combat|Scatter")
	bool bUseScatter = false;
	
	FORCEINLINE float GetDamage() const { return Damage; }
	FORCEINLINE float GetHeadShotDamage() const { return HeadShotDamage; }
	FORCEINLINE ETeam GetTeam() const { return Team; }


protected:

	virtual void BeginPlay() override;
	virtual void OnWeaponStateSet();
	virtual void OnWeaponEquipped();
	virtual void OnWeaponEquippedSecondary();
	virtual void OnWeaponDropped();

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Weapon|Combat")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category = "Weapon|Combat")
	float HeadShotDamage = 40.f;

	/*
	 * Trace end with scatter
	 */
	UPROPERTY(EditAnywhere, Category = "Weapon|Combat|Scatter")
	float ScatterSphereRadius = 75.f;

	UPROPERTY(EditAnywhere, Category = "Weapon|Combat|Scatter")
	float DistanceToScatterSphere = 800.f;

	UPROPERTY(Replicated, EditAnywhere)
	bool bUseServerSideRewind = false;

	UPROPERTY()
	ABlasterCharacter* BlasterOwnerCharacter;

	UPROPERTY()
	ABlasterPlayerController* BlasterOwnerController;

	UFUNCTION()
	void OnPingTooHigh(bool bPingTooHigh);

	UPROPERTY(VisibleAnywhere, Category = "Weapon|Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon|Components")
	USphereComponent* AreaSphere;


private:



	UPROPERTY(VisibleAnywhere, Category = "Weapon|Components")
	UWidgetComponent* PickupWidget;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponState, VisibleAnywhere, Category = "Weapon")
	EWeaponState WeaponState;

	UFUNCTION()
	void OnRep_WeaponState();

	UPROPERTY(EditAnywhere, Category = "Weapon|VFX")
	class UAnimationAsset* FireAnimation;

	UPROPERTY(EditAnywhere, Category = "Weapon|VFX")
	TSubclassOf<class ACasing> CasingClass;

	/*
	 * Zoomed FOV while aiming
	 */

	UPROPERTY(EditAnywhere, Category = "Weapon|VFX")
	float ZoomedFOV = 30.f;

	UPROPERTY(EditAnywhere, Category = "Weapon|VFX")
	float ZoomInterpSpeed = 20.f;

	/*
	 * Ammo
	 */

	UFUNCTION(Client, Reliable)
	void ClientUpdateAmmo(int32 ServerAmmo);

	UFUNCTION(Client, Reliable)
	void ClientAddAmmo(int32 AmmoToAdd);

	void SpendRound();

	UPROPERTY(EditAnywhere, Category = "Weapon|Combat|Ammo")
	int32 Ammo;

	UPROPERTY(EditAnywhere, Category = "Weapon|Combat|Ammo")
	int32 MagCapacity;

	// The number of unprocessed server requests for ammo
	// Incremented in SpendRound, Decremented in ClientUpdateAmmo
	int32 Sequence = 0;

	UPROPERTY(EditAnywhere, Category = "Weapon|Combat")
	EWeaponType WeaponType;

	UPROPERTY()
	FString WeaponName;

	UPROPERTY(EditAnywhere)
	ETeam Team;
};
