// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	private:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool bAlive = true;

	
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* ArmComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;

	void Move(float Value);

	void Rotate(float RValue);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 1000;

	UPROPERTY(EditAnywhere, Category = "Movement");
	float TurnRate = 200;

	APlayerController* TankPlayerController;
	
};
