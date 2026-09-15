// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasketBase.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class APPLEPICKER_API ABasketBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasketBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Paddle1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float BasketSpeed;	// 篮子的速度

	UPROPERTY(EditAnywhere, Category = "Input|Input Mapping")
	UInputMappingContext* DefaultMappingContexts;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void StopMove();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// 会用它把输入动作绑定到具体功能上,这样就能让角色左右移动了
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector CurrentVelocity; // 用这个向量来记录当前当前速度

	void OnMoveRight(float AxisValue);
};
