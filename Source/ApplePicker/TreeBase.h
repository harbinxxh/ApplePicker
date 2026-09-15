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
	float OuterBoundary;

	// Tree randomly redirects only if it is within the inner boundary Smooths the redirection at the outer boundary
	// 只有在内部边界内时，树才会随机改变方向，并在外部边界处平滑过渡改变的方向
	UPROPERTY(EditAnywhere, Category = "Setup")
	float InnerBoundary;

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

	// 改变苹果树方向函数
	void ChangeDirection();

	FTimerHandle AppleSpwnTimer;

	void SpwanApple();
};
