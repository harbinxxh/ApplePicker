// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreeBase.generated.h"

class AAppleBase;

UCLASS()
class APPLEPICKER_API ATreeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TreeMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MovementSpeed;

	// Left and Right boundaries
	// when reached the Tree Actor moves in opposite direction
	UPROPERTY(EditAnywhere, Category = "Setup")
	float Boundary;

	// Change to move in opposite direction
	// 让角色有机会反向移动及重定向概率
	UPROPERTY(EditAnywhere, Category = "Setup")
	float ChanceToRedirect;

	// 重定向时间
	UPROPERTY(EditAnywhere, Category = "Setup")
	float RedirectTime;

	// 用来记录苹果生成的时间间隔
	UPROPERTY(EditAnywhere, Category = "Setup")
	float SecondsBetweenAppleDrops;

	// 可以在编辑器里指定具体的对象
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	TSubclassOf<AAppleBase> SpawnObj;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ChangeDirectionTimer;

	void ChangeDirection();

	FTimerHandle AppleSpwnTimer;

	void SpwanApple();
};
