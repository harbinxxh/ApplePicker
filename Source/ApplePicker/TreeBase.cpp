// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeBase.h"

// Sets default values
ATreeBase::ATreeBase()
	:MovementSpeed(550.0f),	// 初始化移动速度
	Boundary(850.0f),		// 初始化移动边界
	ChanceToRedirect(0.4f),	// 重定向概率
	RedirectTime(1.0f)		// 重定向间隔
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TreeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMeshComponent"));

	RootComponent = TreeMeshComponent;

}

// Called when the game starts or when spawned
void ATreeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(ChangeDirectionTimer, this, &ATreeBase::ChangeDirection, RedirectTime, true, 2.5f);
}

// Called every frame
void ATreeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TempLocation{ GetActorLocation() }; // 返回此 Actor 的根组件的位置

	// Check is Apple Tree within bounds
	if (TempLocation.Y <= -Boundary)
	{
		// Move Right
		MovementSpeed = FMath::Abs(MovementSpeed);
	}
	else if (TempLocation.Y >= Boundary)
	{
		// Move Left
		MovementSpeed = -(FMath::Abs(MovementSpeed));
	}

	// Add offset
	// Set new location
	TempLocation.Y += MovementSpeed * DeltaTime;
	SetActorLocation(TempLocation);

}

void ATreeBase::ChangeDirection()
{
	// 返回一个介于 0 和 1（含）之间的随机浮点数。
	if (FMath::FRand() <= ChanceToRedirect)
	{
		// change direction
		MovementSpeed = MovementSpeed * -1;
	}
}

