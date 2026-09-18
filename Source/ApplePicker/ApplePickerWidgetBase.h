// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ApplePickerWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class APPLEPICKER_API UApplePickerWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	// BlueprintImplementableEvent：该函数可以通过蓝图来实现
	// 设置苹果收集文本
	UFUNCTION(BlueprintImplementableEvent)
	void SetApplesCollectedText(int32 ApplesCollected, int32 ApplesToCollect);

	// 设置游戏结束文本
	UFUNCTION(BlueprintImplementableEvent)
	void SetGameOverText(bool bWonGame);

protected:

	// 开始启动游戏的秒数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float GameStartDelay{ 5.0f };
	
};
