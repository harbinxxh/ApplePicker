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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	int32 ApplesCaught{ 0 };
	int32 ApplesLost{ 0 };

	class ABasketBase* Basket{ nullptr };
};
