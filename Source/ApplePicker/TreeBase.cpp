// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeBase.h"

// Sets default values
ATreeBase::ATreeBase()
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

}

