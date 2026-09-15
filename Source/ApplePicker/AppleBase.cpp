// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleBase.h"

// Sets default values
AAppleBase::AAppleBase()
	:FloorBoundary(-680.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AppleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMeshComponent"));

	RootComponent = AppleMeshComponent;
}

// Called when the game starts or when spawned
void AAppleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAppleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 如果 Actor 的位置，也就是苹果在 Z 轴上的坐标，当 Z 小于或等于设定的地板边界那就直接销毁
	if (GetActorLocation().Z <= FloorBoundary)
	{
		Destroy();
	}
}

