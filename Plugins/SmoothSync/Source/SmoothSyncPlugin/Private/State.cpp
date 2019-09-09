// Fill out your copyright notice in the Description page of Project Settings.

#include "State.h"
#include "SmoothSync.h"


/// Deconstructor
SmoothState::~SmoothState()
{

}

/// <summary>
/// Default constructor. Does nothing.
/// </summary>
SmoothState::SmoothState()
{

}

/// <summary>
/// Returns a Lerped state that is between two States in time.
/// </summary>
void SmoothState::Lerp(SmoothState *targetState, SmoothState *start, SmoothState *end, float t)
{
	targetState->position = FMath::Lerp(start->position, end->position, t);
	targetState->rotation = FMath::Lerp(start->rotation, end->rotation, t);
	targetState->scale = FMath::Lerp(start->scale, end->scale, t);
	targetState->velocity = FMath::Lerp(start->velocity, end->velocity, t);
	targetState->angularVelocity = FMath::Lerp(start->angularVelocity, end->angularVelocity, t);

	targetState->ownerTimestamp = FMath::Lerp(start->ownerTimestamp, end->ownerTimestamp, t);
	targetState->movementMode = start->movementMode;
}

void SmoothState::defaultTheVariables()
{
	ownerTimestamp = 0;
	position = FVector::ZeroVector;
	rotation = FQuat::Identity;
	scale = FVector::ZeroVector;
	velocity = FVector::ZeroVector;
	angularVelocity = FVector::ZeroVector;
	atPositionalRest = false;
	atRotationalRest = false;
	teleport = false;
	movementMode = MOVE_None;
}

void SmoothState::copyFromSmoothSync(USmoothSync *smoothSyncScript)
{
	ownerTimestamp = UGameplayStatics::GetRealTimeSeconds(smoothSyncScript->GetOwner()->GetWorld());

	position = smoothSyncScript->getPosition();
	rotation = smoothSyncScript->getRotation();
	scale = smoothSyncScript->getScale();

	if (smoothSyncScript->isSimulatingPhysics || 
		(smoothSyncScript->characterMovementComponent != nullptr) ||
		(smoothSyncScript->movementComponent != nullptr))
	{
		velocity = smoothSyncScript->getLinearVelocity();
		angularVelocity = smoothSyncScript->getAngularVelocity();
	}
	else
	{
		velocity = FVector::ZeroVector;
		angularVelocity = FVector::ZeroVector;
	}
	if (smoothSyncScript->characterMovementComponent != nullptr)
	{
		movementMode = smoothSyncScript->characterMovementComponent->MovementMode;
	}
}

void SmoothState::copyFromState(SmoothState *state)
{
	ownerTimestamp = state->ownerTimestamp;
	position = state->position;
	rotation = state->rotation;
	scale = state->scale;
	velocity = state->velocity;
	angularVelocity = state->angularVelocity;
	movementMode = state->movementMode;
	teleport = state->teleport;
	atPositionalRest = state->atPositionalRest;
	atRotationalRest = state->atRotationalRest;
}