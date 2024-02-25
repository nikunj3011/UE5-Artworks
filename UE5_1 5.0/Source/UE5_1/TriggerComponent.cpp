// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Trigger component ticked from constructer c++"));

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Trigger component c++"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//TArray<AActor*> Actors;
	//GetOverlappingActors(Actors);

	/*if (Actors.Num() > 0)
	{
		FString Name = Actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Warning, TEXT("Overlapping: %s"), *Name);
	}

	int32 index = 0;
	while (index < Actors.Num())
	{
		FString ActorName = Actors[index]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Warning, TEXT("Overlapping: %s"), *ActorName);
		++index;
	}*/

	/*for (int32 i = 0; i < Actors.Num(); i++)
	{
		FString ActorName = Actors[i]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Warning, TEXT("Overlapping: %s"), *ActorName);
	}*/

	/*for(AActor* Actor : Actors)
	{
		FString ActorName = Actor->GetActorNameOrLabel();
		if (Actor->ActorHasTag(AcceptableTag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlapping and unlocking foreach: %s"), *ActorName);
		}
	}*/

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
		UE_LOG(LogTemp, Warning, TEXT("Unlocking by Actor:"));
	}
	else
	{
		Mover->SetShouldMove(false);
		UE_LOG(LogTemp, Warning, TEXT("Relocking by Actor: "));
	}



}

void UTriggerComponent::SetMover(UPokeMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	//AActor* ReturnActor = nullptr;
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (AActor* Actor : Actors)
	{
		FString ActorName = Actor->GetActorNameOrLabel();
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (HasAcceptableTag && !IsGrabbed)
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlapping and unlocking foreach: %s"), *ActorName);
			return Actor;
		}
	}
	return nullptr;
}
