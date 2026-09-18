// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ApplePickerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class APPLEPICKER_API AApplePickerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// 处理苹果获取
	void HandleAppleCaught();
	
	// 处理苹果丢失
	void HandleAppleLost();

	// 返回开始启动游戏的秒数
	UFUNCTION(BlueprintCallable)
	float GetGameStartDelay() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 处理游戏结束
	// BlueprintNativeEvent：该函数可以被蓝图所覆盖，但同时也具有在C++中的默认实现
	UFUNCTION(BlueprintNativeEvent)
	void HandleGameOver(bool bWonGame);

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 ApplesToCatch{ 10 };

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 ApplesToLose{ 3 };

	// 开始启动游戏的秒数
	UPROPERTY(EditAnywhere, Category = "Setup")
	float GameStartDelay{ 5.0f };

private:
	int32 ApplesCaught{ 0 };
	int32 ApplesLost{ 0 };

	class ABasketBase* Basket{ nullptr };

	// 游戏开始处理逻辑
	void HandleGameStart();

	FTimerHandle GameStartCountdownTimer;
};
