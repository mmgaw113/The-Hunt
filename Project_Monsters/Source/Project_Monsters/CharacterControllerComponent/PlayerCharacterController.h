// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "BaseCharacterController.h"
#include "GameplayTagContainer.h"
#include "PlayerCharacterController.generated.h"

class UTargetingComponent;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UTheHuntGameInstance;
struct FInputActionValue;

UCLASS()
class PROJECT_MONSTERS_API APlayerCharacterController : public ABaseCharacterController
{
	GENERATED_BODY()

public:
	APlayerCharacterController();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Jump() override; 
	virtual void Landed(const FHitResult& Hit) override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	FTimerHandle staminaTimerHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats", meta=(AllowPrivateAccess=true))
	UTheHuntGameInstance* gameInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputMappingContext* mappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PlayerController/Input/IMC_Default.IMC_Default'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* jumpAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Jump.IA_Jump'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lookAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Look.IA_Look'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_LockOn.IA_LockOn'"));;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnActionLeft = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_NextTargetLeft.IA_NextTargetLeft'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnActionRight = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_NextTargetRight.IA_NextTargetRight'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* moveAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Move.IA_Move'"));;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* sprintAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Sprint.IA_Sprint'"));;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UCameraComponent* cameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	USpringArmComponent* springArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UTargetingComponent* targetingComponent;

	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> playerHudClass;
	UPROPERTY()
	class UPlayerHud* playerHud;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AEquipment> leftHandEquipment = LoadObject<UClass>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Weapons/bp_HunterPistol_C.bp_HunterPistol_C'")); 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment", meta=(AllowPrivateAccess=true))
	TSubclassOf<AEquipment> rightHandEquipment = LoadObject<UClass>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Weapons/bp_Sickle_C.bp_Sickle_C'"));
	
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void StopSprint();
	void Stamina(bool Sprinting, bool ReachedZero);
	void RechargeStamina();
	
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar() const;
	
	UFUNCTION(BlueprintCallable)
	void UpdateStaminaBar() const;
	
	UFUNCTION(BlueprintCallable)
	void OnJump();
	
	UFUNCTION(BlueprintCallable)
	void Landed();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GameplayTags", meta=(AllowPrivateAccess))
	FGameplayTag jumpTag;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GameplayTags", meta=(AllowPrivateAccess))
	FGameplayTag staminaTag;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GameplayTags", meta=(AllowPrivateAccess))
	FGameplayTag rechargeTag;
};