// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeBase.h"

// Sets default values
ATreeBase::ATreeBase()
	:MovementSpeed(550.0f),	Boundary(850.0f) // 初始化移动速度和边界
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

