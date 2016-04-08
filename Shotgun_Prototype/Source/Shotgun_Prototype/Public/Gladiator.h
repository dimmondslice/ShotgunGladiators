// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Gladiator.generated.h"

UCLASS()
class SHOTGUN_PROTOTYPE_API AGladiator : public ACharacter
{
	GENERATED_BODY()

	friend class UGladiatorState;

	friend class UIdleState;
	friend class UShootingState;
	friend class UReloadingState;
	friend class URaiseShieldState;
	friend class ULowerShieldState;
	friend class UHoldingShieldState;
	friend class UShieldBashState;
	
	friend class UWalkingState;
	friend class UDodgeState;
	friend class UJumpCrouchState;
	friend class UFallingState;
	friend class ULandingState;

public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
public:
	AGladiator();

//==================================================================================================
//Their Stuff
//==================================================================================================
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AShotgun_PrototypeProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;
	
	/** Fires a projectile. */
	void OnFire();

protected:
	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	* Configures input for touchscreen devices if there is a valid touch interface for doing so
	*
	* @param	InputComponent	The input component pointer to bind controls to
	* @returns true if touch controls were enabled.
	*/
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


//==================================================================================================
//Our Stuff
//==================================================================================================
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWeaponItemBase* HeldWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AShieldItemBase* HeldShield; 

private:
	void SetJumpPressed();
	void SetJumpReleased();
	void SetFirePressed();
	void SetFireReleased();
	void SetReloadPressed();
	void SetReloadReleased();
	void SetShieldPressed();
	void SetShieldReleased();
	void SetDodgePressed();
	void SetDodgeReleased();
	void SetMoveForwardAxis(float val);
	void SetMoveRightAxis(float val);
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void LaunchCharacter_Server(FVector LaunchVelocity, bool bXYOverride, bool bZOverride);



protected:
	bool bJumpAction;
	bool bFireAction;
	bool bReloadAction;
	bool bShieldAction;
	bool bDodgeAction;
	float MoveForwardAxis;
	float MoveRightAxis;
	FVector MoveAxes;

	/**Changes the current upper body state */
	virtual void ChangeUpperState(class UUpperBodyState* newState);
	/**Changes the current lower body state */
	virtual void ChangeLowerState(class ULowerBodyState* newState);
public:	
	//references to every state this gladiator has attached to it
	UPROPERTY(VisibleAnywhere)
	class UIdleState* Idle;
	UPROPERTY(VisibleAnywhere)
	class UShootingState* Shooting;
	UPROPERTY(VisibleAnywhere)
	class UReloadingState* Reloading;
	UPROPERTY(VisibleAnywhere)
	class URaiseShieldState* RaisingShield;
	UPROPERTY(VisibleAnywhere)
	class ULowerShieldState* LowerShield;
	UPROPERTY(VisibleAnywhere)
	class UHoldingShieldState* HoldingShield;
	UPROPERTY(VisibleAnywhere)
	class UShieldBashState* ShieldBash;

	//lower body
	UPROPERTY(VisibleAnywhere)
	class UWalkingState* Walking;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UDodgeState* Dodge;
	UPROPERTY(VisibleAnywhere)
	class UJumpCrouchState* JumpCrouch;
	UPROPERTY(VisibleAnywhere)
	class UFallingState* Falling;
	UPROPERTY(VisibleAnywhere)
	class ULandingState* Landing;

	//Current states for the gladiators upper and lower bodies
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UUpperBodyState* CurrentUpperState;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class ULowerBodyState* CurrentLowerState;
	//These hold the previous state for each half of the body
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UUpperBodyState* PreviousUpperState;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class ULowerBodyState* PreviousLowerState;
};