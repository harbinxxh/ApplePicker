// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplePickerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BasketBase.h"


void AApplePickerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Basket = Cast<ABasketBase>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AApplePickerGameModeBase::HandleAppleCaught()
{
	ApplesCaught = ApplesCaught + 1;

	UE_LOG(LogTemp, Warning, TEXT("Apple Caught!"));
	UE_LOG(LogTemp, Warning, TEXT("Total Apples Caught: %d"), ApplesCaught);
}

void AApplePickerGameModeBase::HandleAppleLost()
{
	ApplesLost = ApplesLost + 1;

	UE_LOG(LogTemp, Warning, TEXT("Apple Lost!"));
	UE_LOG(LogTemp, Warning, TEXT("Total Apples Lost: %d"), ApplesLost);

	if (Basket != nullptr)
	{
		Basket->HandlePaddleDestruction();
	}

	//TODO: Stop Spawning Apples

	//TODO: Destroy Remaining Apples
}

