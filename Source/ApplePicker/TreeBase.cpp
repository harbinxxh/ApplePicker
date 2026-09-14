// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeBase.h"
#include "AppleBase.h"

// Sets default values
ATreeBase::ATreeBase() :
	MovementSpeed(550.0f),			// 初始化移动速度
	Boundary(850.0f),				// 初始化移动边界
	ChanceToRedirect(0.4f),			// 重定向概率
	RedirectTime(1.0f),				// 重定向间隔
	SecondsBetweenAppleDrops(1.0f)	// 用来记录苹果生成的时间间隔
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

	GetWorld()->GetTimerManager().SetTimer(AppleSpwnTimer, this, &ATreeBase::SpwanApple, SecondsBetweenAppleDrops, true, 2.0f);
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

// 让苹果随机出现在苹果树的左边或者右边，带点偏移
void ATreeBase::SpwanApple()
{
	// Get TreeBase current location
	// 获取 TreeBase 的当前位置
	FVector SpawnLoc = GetActorLocation();
	FRotator SpawnRot = GetActorRotation();

	// Add offset randomly to the left or to the right of the current location
	// 随机向当前位置的左侧或右侧添加偏移量
	if (FMath::FRand() <= 0.5f)
	{
		SpawnLoc.Y += 150.0f;
	}
	else
	{
		SpawnLoc.Y -= 150.0f;
	}

	// Spawn apple at new offset location
	// 在新的偏移位置生成苹果
	GetWorld()->SpawnActor<AAppleBase>(SpawnObj, SpawnLoc, SpawnRot);
}

