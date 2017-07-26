// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "TankAimingComponent.h"
#include "Tank.h"

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
	//UE_LOG(LogTemp, Warning, TEXT("Moving toward %f,%f with ar: %f"), PlayerPawn->GetActorLocation().X, PlayerPawn->GetActorLocation().Y, AcceptanceRadius);
	MoveToActor(PlayerPawn, AcceptanceRadius); // TODO check radius is in centimeters

	// Aim towards the player
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());

	// Fire if ready
	if (AimingComponent->GetFiringState() == EFiringState::Ready) 
	{
		AimingComponent->Fire(); // TODO limit firing rate
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) 
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::ProcessPossessedTankDeath);
	}
}

void ATankAIController::ProcessPossessedTankDeath() 
{
	UE_LOG(LogTemp, Warning, TEXT("My tank died :("));
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}