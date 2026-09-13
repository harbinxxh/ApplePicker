// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleBase.h"

// Sets default values
AAppleBase::AAppleBase()
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

}

