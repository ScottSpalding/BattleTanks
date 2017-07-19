// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "TankAimingComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Depends on MovementComponent via pathfinding system

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(GetPawn()) || !ensure(AimingComponent)) { return; }

	// Move towards the player
	MoveToActor(PlayerPawn, AcceptanceRadius); // TODO check radius is in centimeters

	// Aim towards the player
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());

	// Fire if ready
	AimingComponent->Fire(); // TODO limit firing rate
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}