// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, +1.f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewYaw = RelativeRotation.Yaw + ElevationChange;
	SetRelativeRotation(FRotator(0, NewYaw, 0));
}