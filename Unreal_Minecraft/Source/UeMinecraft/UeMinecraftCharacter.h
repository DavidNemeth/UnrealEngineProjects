// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Block.h"
#include "Wieldable.h"
#include "UeMinecraftCharacter.generated.h"

class UInputComponent;

UCLASS(config = Game)
class AUeMinecraftCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

public:
	AUeMinecraftCharacter();

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_WieldedItem;

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
		TSubclassOf<class AUeMinecraftProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		uint32 bUsingMotionControllers : 1;

	/*Gets current inventory slot for the HUD*/
	UFUNCTION(BlueprintPure, Category = HUD)
		int32 GetCurrentInventorySlot();

	/*Adds an item to our inventory*/
	UFUNCTION(BlueprintCallable, Category = Inventory)
		bool AddItemToInventory(AWieldable* Item);

	UFUNCTION(BlueprintPure, Category = Inventory)
		UTexture2D* GetThumbnailAtInventorySlot(uint8 Slot);

	/*The type of tool and material of the currently wielded item*/
	uint8 ToolType;	
	uint8 MaterialType;

	UPROPERTY(EditAnywhere)
		TArray<AWieldable*> Inventory;
protected:

	/** Fires a projectile. */
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

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

private:

	/*Number of inventory slots*/
	const int32 NUM_OF_INVENTORY_SLOTS = 10;

	/*Current inventory slot*/
	int32 CurrentInventorySlot;

	/*Update the wielded item*/
	void UpdateWieldedItem();

	/*Gets the currently wielded item*/
	AWieldable* GetCurrentlyWieldedItem();

	/*Drops the currently wielded item*/
	void Throw();

	/*Increment and decrement inventory slot*/
	void MoveUpInventorySlot();
	void MoveDownInventorySlot();

	/*True if player is breaking block*/
	bool bIsBreaking;

	/*Called when hitting with a tool*/
	void OnHit();
	void EndHit();

	/*Plays the mining animation*/
	void PlayHitAnim();


	/*Check if player looking at a block*/
	void CheckForBlocks();

	/*called when we want to break a block*/
	void BreakBlock();

	/*Store the currently being looked at block*/
	ABlock* CurrentBlock;

	/*character reach*/
	float Reach;

	/*Timer handles*/
	FTimerHandle BlockBreakingHandle;
	FTimerHandle HitAnimHandle;

public:
	/** Returns Mesh1P sub-object **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent sub-object **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

