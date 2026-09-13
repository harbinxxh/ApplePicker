// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreeBase.generated.h"

UCLASS()
class APPLEPICKER_API ATreeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TreeMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MovementSpeed;

	// Left and Right boundaries
	// when reached the Tree Actor moves in opposite direction
	UPROPERTY(EditAnywhere, Category = "Setup")
	float Boundary;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
