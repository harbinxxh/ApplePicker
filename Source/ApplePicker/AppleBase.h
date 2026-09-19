// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AppleTreeElementBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppleBase.generated.h"

UCLASS()
class APPLEPICKER_API AAppleBase : public AAppleTreeElementBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAppleBase();

	virtual void Destroyed() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* AppleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle Effects")
	class UNiagaraSystem* AppleDestroyedParticles;
	
	// 苹果掉落，超出地板的位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float FloorBoundary;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	class AApplePickerGameModeBase* CurrentGameMode{ nullptr };
};
