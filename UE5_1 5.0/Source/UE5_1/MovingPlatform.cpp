// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	myIntA = 9;
	myIntSum = myIntA + myIntB;
	MyFloatX = MyVector.X;
	MyVector.X = 5;
	SetActorLocation(FVector(1,2,3));
	StartLocation = GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("Moved Distance: %f"), MovedDistance);

	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("Begin Play: %s"), *Name);

	// UE_LOG(LogTemp, Display, TEXT("hie"));
	// UE_LOG(LogTemp, Warning, TEXT("hie"));
	// UE_LOG(LogTemp, Error, TEXT("hie"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// FVector LocalVector = MyVector;
	// LocalVector.Z = LocalVector.Z + 100;
	// MyVector.Y = MyVector.Y + 1; 
	// SetActorLocation(LocalVector);

	//Move actor using its location
 	MovePlatform(DeltaTime);
 	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if(ShouldPlatformReturn())
	{
		// float OverShoot = DistanceFromPlatform - MovedDistance;
		// FString Name = GetName();
		// UE_LOG(LogTemp, Display, TEXT("%s Platform overshoot by  Moved Distance: %f"), Name, OverShoot);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		// CurrentLocation.X = CurrentLocation.X + 1;
		CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
		// float DistanceFromPlatform = FVector::Dist(StartLocation, CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	// FRotator CurrentLocation = GetActorRotation();
	// CurrentLocation = CurrentLocation + RotationVelocity * DeltaTime;
	// SetActorRotation(CurrentLocation);
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	float DistanceMoved = FVector::Dist(StartLocation, GetActorLocation());
	return DistanceMoved > MovedDistance;
}

