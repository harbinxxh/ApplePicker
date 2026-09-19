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

	// 处理挡板销毁
	void HandlePaddleDestruction();

	// 获取玩家控制器
	APlayerController* GetBasketPlayerController() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 对于静态放置的 Actor 和具有原生根组件的生成 Actor，此函数现在会被调用。
	// 对于没有原生根组件的蓝图 Actor，这些注册函数会在构造过程中稍后调用。
	virtual void PreRegisterAllComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Paddle1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Paddle2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Paddle3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle Effects")
	class UNiagaraSystem* PaddleLostParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float BasketSpeed;	// 篮子的速度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FVector PaddleOffset;

	UPROPERTY(EditAnywhere, Category = "Input|Input Mapping")
	UInputMappingContext* DefaultMappingContexts;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void StopMove();

	// 必须用 UFunction 宏标记 onHit 成员函数，因为后面要把它绑定到事件或委托
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// 会用它把输入动作绑定到具体功能上,这样就能让角色左右移动了
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector CurrentVelocity; // 用这个向量来记录当前当前速度

	class AApplePickerGameModeBase* CurrentGameMode{ nullptr };

	void OnMoveRight(float AxisValue);

	// 挡板数组
	TArray<UStaticMeshComponent*> PaddleArray;

	APlayerController* Controller{ nullptr };
};
