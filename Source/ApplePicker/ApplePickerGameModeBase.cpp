// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplePickerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BasketBase.h"
#include "AppleBase.h"
#include "TreeBase.h"


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

	if (ApplesLost >= 3)
	{
		//TODO: Stop Spawning Apples
		TArray<AActor*> FoundTrees;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATreeBase::StaticClass(), FoundTrees);

		for (auto Ptr : FoundTrees)
		{
			ATreeBase* PtrTemp = Cast<ATreeBase>(Ptr);
			if (PtrTemp != nullptr)
			{
				PtrTemp->StopSpawningApples();
			}
		}

		//TODO: Destroy Remaining Apples
		TArray<AActor*> FoundApples;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAppleBase::StaticClass(), FoundApples);

		for (auto Ptr : FoundApples)
		{
			AAppleBase* PtrTemp = Cast<AAppleBase>(Ptr);
			if (PtrTemp != nullptr)
			{
				PtrTemp->Destroy();
			}
		}
	}
}

