// Fill out your copyright notice in the Description page of Project Settings.


#include "PokeMover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UPokeMover::UPokeMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPokeMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetOwner()->GetActorLocation();
	// ...

}


// Called every frame
void UPokeMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector TargetLocation = OriginalLocation;
	if (ShouldMove)
	{
		TargetLocation = TargetLocation + MoveOffset;
		//AActor* Owner = GetOwner();
		//// FString Name = (*Owner).GetActorNameOrLabel();
		//FString Name = Owner->GetActorNameOrLabel();
		//FVector Location = Owner->GetActorLocation();
		//FString LocationString = Location.ToCompactString();
		//UE_LOG(LogTemp, Display, TEXT("Owner Address: %s, Location: %s"), *Name, *LocationString);
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	//FVector TargetLocation = OriginalLocation + MoveOffset;
	float Speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);
	// ...
}

void UPokeMover::SetShouldMove(bool NewShouldMove)
{
	try
	{
		ShouldMove = NewShouldMove;
	}
	catch (const std::exception&)
	{

	}
}

