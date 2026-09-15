// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "AppleBase.h"

// Sets default values
ABasketBase::ABasketBase()
	: BasketSpeed(700.0f), CurrentVelocity(0.0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));

	RootComponent = Root;
	Paddle1->SetupAttachment(RootComponent);

	// 确定在关卡开始或角色生成时，应自动拥有该Pawn的PlayerController（如果存在的话）
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABasketBase::BeginPlay()
{
	Super::BeginPlay();
	
	Paddle1->OnComponentHit.AddDynamic(this, &ABasketBase::OnHit);
}

void ABasketBase::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	// X：Right Y: Forward
	OnMoveRight(MovementVector.X);
}

void ABasketBase::StopMove()
{
	CurrentVelocity.X = 0.0;
	CurrentVelocity.Y = 0.0;
}

void ABasketBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit)
{
	AAppleBase* AppleToCatch = Cast<AAppleBase>(OtherActor);

	if (AppleToCatch)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABasketBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ABasketBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContexts, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasketBase::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABasketBase::Move);
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABasketBase::StopMove);
	}
}

void ABasketBase::OnMoveRight(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * BasketSpeed;

	//UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *CurrentVelocity.ToString());
}