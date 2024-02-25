// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class UE5_1_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int32 myIntA = 99;

	UPROPERTY(EditAnywhere)
	int32 myIntB = 99;

	UPROPERTY(EditAnywhere)
	int32 myIntSum = 0;

	UPROPERTY(EditAnywhere)
	FVector MyVector = FVector(1, 2, 3);

	UPROPERTY(VisibleAnywhere)
	float MyFloatX = 0;

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	FVector PlatformVelocity = FVector(100, 0, 0);

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	double MovedDistance = 300;

	UPROPERTY(EditAnywhere, Category="Rotation Platform")
	FRotator RotationVelocity;

	FVector StartLocation;

	// UPROPERTY(VisibleAnywhere, Category="Moving Platform")
	// double DistanceFromPlatform = -1;
	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn() const;
};
