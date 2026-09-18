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
	if (Basket)
	{
		// 游戏启动时，先禁用游戏输入
		Basket->DisableInput(nullptr);
	}

	// 游戏启动定时器
	GetWorld()->GetTimerManager().SetTimer(GameStartCountdownTimer
										, this
										, &ThisClass::HandleGameStart
										, GameStartDelay
										, false);
}

void AApplePickerGameModeBase::HandleAppleCaught()
{
	ApplesCaught = ApplesCaught + 1;

	UE_LOG(LogTemp, Warning, TEXT("Apple Caught!"));
	UE_LOG(LogTemp, Warning, TEXT("Total Apples Caught: %d"), ApplesCaught);

	if (ApplesCaught >= ApplesToCatch)
	{
		// We win the game
		HandleGameOver(true);
	}
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

	if (ApplesLost >= ApplesToLose)
	{
		// We lose the game
		HandleGameOver(false);
	}
}

void AApplePickerGameModeBase::HandleGameOver_Implementation(bool bWonGame)
{
	TArray<AActor*> FoundAppleTreeElements;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAppleTreeElementBase::StaticClass(), FoundAppleTreeElements);

	for (auto Ptr : FoundAppleTreeElements)
	{
		if (ATreeBase* TempTreePtr = Cast<ATreeBase>(Ptr))
		{
			// stop spawning apples
			TempTreePtr->StopSpawningApples();

			// stop redirecting
			TempTreePtr->StopRedirecting();

			// set should move to false
			TempTreePtr->SetShouldMove(false);
		}
		else if (AAppleBase* TempApplePtr = Cast<AAppleBase>(Ptr))
		{
			//TODO: Destroy Remaining Apples
			TempApplePtr->Destroy();
		}
	}

	if (Basket && Basket->GetBasketPlayerController())
	{
		// 禁用玩家输入
		Basket->DisableInput(Basket->GetBasketPlayerController());
		// 关闭Pawn定时器
		Basket->SetActorTickEnabled(false);
		//Basket->SetActorHiddenInGame(true);
	}
}

// 游戏开始处理逻辑
void AApplePickerGameModeBase::HandleGameStart()
{
	TArray<AActor*> FoundAppleTreeElements;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAppleTreeElementBase::StaticClass(), FoundAppleTreeElements);

	for (auto Ptr : FoundAppleTreeElements)
	{
		if (ATreeBase* TempTreePtr = Cast<ATreeBase>(Ptr))
		{
			// start spawning apples
			TempTreePtr->StartSpawningApples();

			// start redirecting
			TempTreePtr->StartRedirecting();

			// set should move to false
			TempTreePtr->SetShouldMove(true);
		}
	}

	if (Basket && Basket->GetBasketPlayerController())
	{
		// 启动玩家输入
		Basket->EnableInput(Basket->GetBasketPlayerController());
		// 启动 Pawn 定时器
		Basket->SetActorTickEnabled(true);
	}
}
