// Fill out your copyright notice in the Description page of Project Settings.

#include "SmoothSync.h"
#include "State.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"



// Sets default values for this component's properties
USmoothSync::USmoothSync()
{
	// So the component can tick every frame.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called whenever this actor is being removed from a level
void USmoothSync::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Check if we have a stateBuffer variable we need to cleanup.
	if (stateBuffer != NULL)
	{
		delete[] stateBuffer;
	}
}

// Native event for when play begins for this actor.
void USmoothSync::BeginPlay()
{
	Super::BeginPlay();

	realObjectToSync = GetOwner();
	movementComponent = (UMovementComponent*)realObjectToSync->FindComponentByClass(UMovementComponent::StaticClass());
	characterMovementComponent = (UCharacterMovementComponent*)realObjectToSync->FindComponentByClass(UCharacterMovementComponent::StaticClass());

	// If haven't chosen to sync a specific component, set it up to sync the root component.
	if (realComponentToSync == nullptr)
	{
		primitiveComponent = Cast<UPrimitiveComponent>(realObjectToSync->GetRootComponent());

		if (primitiveComponent && primitiveComponent->IsSimulatingPhysics())
		{
			isSimulatingPhysics = true;
			//if (realObjectToSync->GetOwner() != UGameplayStatics::GetPlayerController(GetWorld(), 0))
			//{
			//	//primitiveComponent->SetEnableGravity(false);
			//}
		}
	}

	// Setup some variable states for use.
	sendingTempState = new SmoothState();
	targetTempState = new SmoothState();
	stateBuffer = new SmoothState*[std::max(calculatedStateBufferSize, 30)];
	int stateBufferLength = std::max(calculatedStateBufferSize, 30);
	for (int i = 0; i < stateBufferLength; i++)
	{
		stateBuffer[i] = NULL;
	}

	// If we want to extrapolate forever, force variables accordingly. 
	if (extrapolationMode == ExtrapolationMode::UNLIMITED)
	{
		useExtrapolationDistanceLimit = false;
		useExtrapolationTimeLimit = false;
	}

	// We need to do this in order to send unreliable RPCs?
	SetIsReplicated(true);
}

/// <summary>
/// If you want to track a scene component, assign it, otherwise it will just sync the actor the SmoothSync is on.
/// Must have one SmoothSync for each Transform that you want to sync.
/// <summary>
void USmoothSync::setSceneComponentToSync(USceneComponent *componentToSync)
{
	realComponentToSync = componentToSync;
	primitiveComponent = Cast<UPrimitiveComponent>(realComponentToSync);
	if (primitiveComponent && primitiveComponent->IsSimulatingPhysics())
	{
		isSimulatingPhysics = true;
	}
	else
	{
		isSimulatingPhysics = false;
	}
}

template <class T>
void USmoothSync::copyToBuffer(T thing)
{
	uint8* thingAsChars = (uint8*)&thing;
	for (int i = 0; i < sizeof(T); i++)
	{
		sendingCharArray.Add(thingAsChars[i]);
	}

	sendingCharArraySize += sizeof(T);
}

template <class T>
void USmoothSync::readFromBuffer(T* thing)
{
	uint8* thingAsChars = (uint8*)thing;
	for (int i = 0; i < sizeof(T); i++)
	{
		thingAsChars[i] = readingCharArray[readingCharArraySize + i];
	}

	readingCharArraySize += sizeof(T);
}

/// <summary>
/// Encode sync info based on what we want to send.
/// </summary>
char USmoothSync::encodeSyncInformation(bool sendPositionFlag, bool sendRotationFlag, bool sendScaleFlag, bool sendVelocityFlag,
	bool sendAngularVelocityFlag, bool atPositionalRestFlag, bool atRotationalRestFlag, bool sendMovementModeFlag)
{
	char encoded = 0;

	if (sendPositionFlag)
	{
		encoded = (char)(encoded | positionMask);
	}
	if (sendRotationFlag)
	{
		encoded = (char)(encoded | rotationMask);
	}
	if (sendScaleFlag)
	{
		encoded = (char)(encoded | scaleMask);
	}
	if (sendVelocityFlag)
	{
		encoded = (char)(encoded | velocityMask);
	}
	if (sendAngularVelocityFlag)
	{
		encoded = (char)(encoded | angularVelocityMask);
	}
	if (atPositionalRestFlag)
	{
		encoded = (char)(encoded | atPositionalRestMask);
	}
	if (atRotationalRestFlag)
	{
		encoded = (char)(encoded | atRotationalRestMask);
	}
	if (sendMovementModeFlag)
	{
		encoded = (char)(encoded | movementModeMask);
	}
	return encoded;
}
/// <summary>
/// Decode sync info to see if we want to sync position.
/// </summary>
bool USmoothSync::shouldDeserializePosition(char syncInformation)
{
	if ((syncInformation & positionMask) == positionMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Decode sync info to see if we want to sync rotation.
/// </summary>
bool USmoothSync::shouldDeserializeRotation(char syncInformation)
{
	if ((syncInformation & rotationMask) == rotationMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Decode sync info to see if we want to sync scale.
/// </summary>
bool USmoothSync::shouldDeserializeScale(char syncInformation)
{
	if ((syncInformation & scaleMask) == scaleMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Decode sync info to see if we want to sync velocity.
/// </summary>
bool USmoothSync::shouldDeserializeVelocity(char syncInformation)
{
	if ((syncInformation & velocityMask) == velocityMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Decode sync info to see if we want to sync angular velocity.
/// </summary>
bool USmoothSync::shouldDeserializeAngularVelocity(char syncInformation)
{
	if ((syncInformation & angularVelocityMask) == angularVelocityMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Decode sync info to see if we want to sync angular velocity.
/// </summary>
bool USmoothSync::deserializePositionalRestFlag(char syncInformation)
{
	if ((syncInformation & atPositionalRestMask) == atPositionalRestMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Decode sync info to see if we want to sync angular velocity.
/// </summary>
bool USmoothSync::deserializeRotationalRestFlag(char syncInformation)
{
	if ((syncInformation & atRotationalRestMask) == atRotationalRestMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Decode sync info to see if we want to sync angular velocity.
/// </summary>
bool USmoothSync::shouldDeserializeMovementMode(char syncInformation)
{
	if ((syncInformation & movementModeMask) == movementModeMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool USmoothSync::SmoothSyncTeleportClientToServer_Validate(FVector position, FVector rotation, FVector scale, float tempOwnerTime)
{
	return true;
}
void USmoothSync::SmoothSyncTeleportClientToServer_Implementation(FVector position, FVector rotation, FVector scale, float tempOwnerTime)
{
	SmoothSyncTeleportServerToClients(position, rotation, scale, tempOwnerTime);
}
bool USmoothSync::SmoothSyncTeleportServerToClients_Validate(FVector position, FVector rotation, FVector scale, float tempOwnerTime)
{
	return true;
}
void USmoothSync::SmoothSyncTeleportServerToClients_Implementation(FVector position, FVector rotation, FVector scale, float tempOwnerTime)
{
	// Only set up new State if we aren't the system determining the Transform.
	if (!shouldSendTransform())
	{
		SmoothState *teleportState = new SmoothState();
		teleportState->copyFromSmoothSync(this);
		teleportState->position = position;
		teleportState->rotation = FQuat::MakeFromEuler(rotation);
		teleportState->ownerTimestamp = tempOwnerTime;
		teleportState->teleport = true;

		addTeleportState(teleportState);
	}
}


bool USmoothSync::SmoothSyncEnableClientToServer_Validate(bool enable)
{
	return true;
}
void USmoothSync::SmoothSyncEnableClientToServer_Implementation(bool enable)
{
	SmoothSyncEnableServerToClients(enable);
}
bool USmoothSync::SmoothSyncEnableServerToClients_Validate(bool enable)
{

	return true;
}
void USmoothSync::SmoothSyncEnableServerToClients_Implementation(bool enable)
{
	internalEnableSmoothSync(enable);
}


bool USmoothSync::ClientSendsTransformToServer_Validate(const TArray<uint8>& value)
{
	return true;
}
void USmoothSync::ClientSendsTransformToServer_Implementation(const TArray<uint8>& value)
{
	ServerSendsTransformToEveryone(value);
}

bool USmoothSync::ServerSendsTransformToEveryone_Validate(const TArray<uint8>& value)
{
	return true;
}

void USmoothSync::ServerSendsTransformToEveryone_Implementation(const TArray<uint8>& value)
{
	// If we should be sending the Transform, there's no reason to do anything with the received message.
	if (shouldSendTransform())
	{
		return;
	}

	// Reset array variables to default
	readingCharArraySize = 0;
	readingCharArray.Empty();
	// Assign the array
	readingCharArray = value;

	SmoothState *stateToAdd = new SmoothState();

	// The first received byte tells us what we need to be syncing.
	char syncInfoByte;
	readFromBuffer(&syncInfoByte);
	bool deserializePosition = shouldDeserializePosition(syncInfoByte);
	bool deserializeRotation = shouldDeserializeRotation(syncInfoByte);
	bool deserializeScale = shouldDeserializeScale(syncInfoByte);
	bool deserializeVelocity = shouldDeserializeVelocity(syncInfoByte);
	bool deserializeAngularVelocity = shouldDeserializeAngularVelocity(syncInfoByte);
	bool deserializeMovementMode = shouldDeserializeMovementMode(syncInfoByte);
	stateToAdd->atPositionalRest = deserializePositionalRestFlag(syncInfoByte);
	stateToAdd->atRotationalRest = deserializeRotationalRestFlag(syncInfoByte);

	readFromBuffer(&(stateToAdd->ownerTimestamp));

	if (characterMovementComponent != nullptr)
	{
		readFromBuffer(&deserializeMovementMode);
		if (deserializeMovementMode)
		{
			uint8 tempMovementMode;
			readFromBuffer(&tempMovementMode);
			stateToAdd->movementMode = tempMovementMode;
			latestReceivedMovementMode = tempMovementMode;
		}
		else
		{
			stateToAdd->movementMode = latestReceivedMovementMode;
		}
	}

	if (!realObjectToSync)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find target for network state message."));
		return;
	}

	if (receivedStatesCounter < sendRate) receivedStatesCounter++;

	// Read position.
	if (deserializePosition)
	{
		if (isPositionCompressed)
		{
			FFloat16 tempX, tempY, tempZ;
			if (isSyncingXPosition())
			{
				readFromBuffer(&(tempX));
				stateToAdd->position.X = float(tempX);
			}
			if (isSyncingYPosition())
			{
				readFromBuffer(&(tempY));
				stateToAdd->position.Y = float(tempY);
			}
			if (isSyncingZPosition())
			{
				readFromBuffer(&(tempZ));
				stateToAdd->position.Z = float(tempZ);
			}
			// Multiply by 100 to fully decompress since we divided by 100 when sending.
			stateToAdd->position = stateToAdd->position * 100.0f;
		}
		else
		{
			if (isSyncingXPosition())
			{
				readFromBuffer(&(stateToAdd->position.X));
			}
			if (isSyncingYPosition())
			{
				readFromBuffer(&(stateToAdd->position.Y));
			}
			if (isSyncingZPosition())
			{
				readFromBuffer(&(stateToAdd->position.Z));
			}
		}
	}
	else
	{
		if (stateCount > 0)
		{
			stateToAdd->position = stateBuffer[0]->position;
		}
		else
		{
			stateToAdd->position = getPosition();
		}
	}
	// Read rotation.
	if (deserializeRotation)
	{
		float rotX = 0;
		float rotY = 0;
		float rotZ = 0;
		if (isRotationCompressed)
		{
			FFloat16 tempX, tempY, tempZ;
			if (isSyncingXRotation())
			{
				readFromBuffer(&(tempX));
				rotX = float(tempX);
			}
			if (isSyncingYRotation())
			{
				readFromBuffer(&(tempY));
				rotY = float(tempY);
			}
			if (isSyncingZRotation())
			{
				readFromBuffer(&(tempZ));
				rotZ = float(tempZ);
			}
			FVector rot = FVector(rotX, rotY, rotZ);
			stateToAdd->rotation = FQuat::MakeFromEuler(rot);
		}
		else
		{
			if (isSyncingXRotation())
			{
				readFromBuffer(&rotX);
			}
			if (isSyncingYRotation())
			{
				readFromBuffer(&rotY);
			}
			if (isSyncingZRotation())
			{
				readFromBuffer(&rotZ);
			}
			FVector rot = FVector(rotX, rotY, rotZ);
			stateToAdd->rotation = FQuat::MakeFromEuler(rot);
		}
	}
	else
	{
		if (stateCount > 0)
		{
			stateToAdd->rotation = stateBuffer[0]->rotation;
		}
		else
		{
			stateToAdd->rotation = getRotation();
		}
	}
	// Read scale.
	if (deserializeScale)
	{
		if (isScaleCompressed)
		{
			FFloat16 tempX, tempY, tempZ;
			if (isSyncingXScale())
			{
				readFromBuffer(&(tempX));
				stateToAdd->scale.X = float(tempX);
			}
			if (isSyncingYScale())
			{
				readFromBuffer(&(tempY));
				stateToAdd->scale.Y = float(tempY);
			}
			if (isSyncingZScale())
			{
				readFromBuffer(&(tempZ));
				stateToAdd->scale.Z = float(tempZ);
			}
		}
		else
		{
			if (isSyncingXScale())
			{
				readFromBuffer(&(stateToAdd->scale.X));
			}
			if (isSyncingYScale())
			{
				readFromBuffer(&(stateToAdd->scale.Y));
			}
			if (isSyncingZScale())
			{
				readFromBuffer(&(stateToAdd->scale.Z));
			}
		}
	}
	else
	{
		if (stateCount > 0)
		{
			stateToAdd->scale = stateBuffer[0]->scale;
		}
		else
		{
			stateToAdd->scale = getScale();
		}
	}
	// Read velocity.
	if (deserializeVelocity)
	{
		if (isVelocityCompressed)
		{
			FFloat16 tempX, tempY, tempZ;
			if (isSyncingXVelocity())
			{
				readFromBuffer(&(tempX));
				stateToAdd->velocity.X = float(tempX);
			}
			if (isSyncingYVelocity())
			{
				readFromBuffer(&(tempY));
				stateToAdd->velocity.Y = float(tempY);
			}
			if (isSyncingZVelocity())
			{
				readFromBuffer(&(tempZ));
				stateToAdd->velocity.Z = float(tempZ);
			}
		}
		else
		{
			if (isSyncingXVelocity())
			{
				readFromBuffer(&(stateToAdd->velocity.X));
			}
			if (isSyncingYVelocity())
			{
				readFromBuffer(&(stateToAdd->velocity.Y));
			}
			if (isSyncingZVelocity())
			{
				readFromBuffer(&(stateToAdd->velocity.Z));
			}
		}
		latestReceivedVelocity = stateToAdd->velocity;
	}
	else
	{
		// If we didn't receive an updated velocity, use the latest received velocity.
		stateToAdd->velocity = latestReceivedVelocity;
	}
	// Read anguluar velocity.
	if (deserializeAngularVelocity)
	{
		if (isAngularVelocityCompressed)
		{
			FFloat16 tempX, tempY, tempZ;
			if (isSyncingXAngularVelocity())
			{
				readFromBuffer(&(tempX));
				stateToAdd->angularVelocity.X = float(tempX);
			}
			if (isSyncingYAngularVelocity())
			{
				readFromBuffer(&(tempY));
				stateToAdd->angularVelocity.Y = float(tempY);
			}
			if (isSyncingZAngularVelocity())
			{
				readFromBuffer(&(tempZ));
				stateToAdd->angularVelocity.Z = float(tempZ);
			}
		}
		else
		{
			if (isSyncingXAngularVelocity())
			{
				readFromBuffer(&(stateToAdd->angularVelocity.X));
			}
			if (isSyncingYAngularVelocity())
			{
				readFromBuffer(&(stateToAdd->angularVelocity.Y));
			}
			if (isSyncingZAngularVelocity())
			{
				readFromBuffer(&(stateToAdd->angularVelocity.Z));
			}
		}
		latestReceivedAngularVelocity = stateToAdd->angularVelocity;
	}
	else
	{
		stateToAdd->angularVelocity = latestReceivedAngularVelocity;
	}

	addState(stateToAdd);
}

// Called every frame
void USmoothSync::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!isBeingUsed) return;

	updatedDeltaTime = DeltaTime;

	bool sendTransform = shouldSendTransform();

	// Set the interpolated / extrapolated Transforms and Rigidbodies if we shouldn't send Transform.
	if (!sendTransform)
	{
		adjustOwnerTime();
		applyInterpolationOrExtrapolation();
	}
	else // Send out Transform if we are should send Transform.
	{
		sendState();
	}

	// Set up variables to check against next frame.
	if (samePositionCount == 0 && restStatePosition != RestState::AT_REST)
	{
		positionLastFrame = getPosition();
	}
	if (sameRotationCount == 0 && restStateRotation != RestState::AT_REST)
	{
		rotationLastFrame = getRotation();
	}
	// Reset back to default bools.
	resetFlags();
}
/// <summary>Used to turn Smooth Sync on and off. True to enable Smooth Sync. False to disable Smooth Sync.</summary>
///	<remarks>Will automatically send RPCs across the network. Is meant to be called on the owned version of the Actor.</remarks>
void USmoothSync::enableSmoothSync(bool enable)
{
	if (shouldSendTransform())
	{
		if (realObjectToSync->GetWorld()->IsServer())
		{
			SmoothSyncEnableServerToClients(enable);
		}
		else
		{
			SmoothSyncEnableClientToServer(enable);
		}
	}
}

void USmoothSync::internalEnableSmoothSync(bool enable)
{
	if (enable)
	{
		isBeingUsed = true;
	}
	else
	{
		isBeingUsed = false;
		clearBuffer();
	}
}

/// <summary>
/// Determines if we should be trying to send out the Transform.
/// </summary>
/// <remarks>
/// Rules for sending Transform.
/// Owned Actors: Owner determines position and sends out Transform.
/// Unowned Actors: Server determines position and sends out Transform.
/// </remarks>
bool USmoothSync::shouldSendTransform()
{
	if (GetWorld()->IsServer())
	{
		if (APawn* pawn = Cast<APawn>(GetOwner()))
		{
			if (pawn != NULL && !pawn->IsLocallyControlled() && pawn->IsControlled())
			{
				return false;
			}
		}

		// If object to Sync is not found, don't send information out.
		if (realObjectToSync == nullptr) return false;

		if (GetNetMode() == NM_DedicatedServer)
		{
			for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
			{
				APlayerController* PC = Cast<APlayerController>(*Iterator);
				if (realObjectToSync->GetOwner() == PC)
				{
					return false;
				}
			}
		}
		else
		{
			for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
			{
				APlayerController* PC = Cast<APlayerController>(*Iterator);
				if (realObjectToSync->GetOwner() == PC &&
					realObjectToSync->GetOwner() != UGameplayStatics::GetPlayerController(GetWorld(), 0))
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		if (APawn* pawn = Cast<APawn>(GetOwner()))
		{
			if (pawn != NULL && pawn->IsLocallyControlled())
			{
				return true;
			}
		}
		else if (realObjectToSync != nullptr &&
			realObjectToSync->GetOwner() == UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			return true;
		}
	}

	return false;
}

void USmoothSync::sendState()
{
	if (extrapolationMode != ExtrapolationMode::NONE)
	{
		// Same position logic.
		if (syncPosition != SyncMode::NONE)
		{
			if (sameVector(positionLastFrame, getPosition(), atRestPositionThreshold))
			{
				if (restStatePosition != RestState::AT_REST)
				{
					samePositionCount += updatedDeltaTime;
				}
				if (samePositionCount >= atRestThresholdCount)
				{
					samePositionCount = 0;
					restStatePosition = RestState::AT_REST;
					forceStateSendNextFrame();
				}
			}
			else
			{
				if (restStatePosition == RestState::AT_REST && getPosition() != latestTeleportedFromPosition)
				{
					restStatePosition = RestState::JUST_STARTED_MOVING;
					forceStateSendNextFrame();
				}
				else if (restStatePosition == RestState::JUST_STARTED_MOVING)
				{
					restStatePosition = RestState::MOVING;
					//forceStateSendNextFixedUpdate();
				}
				else
				{
					samePositionCount = 0;
				}
			}
		}
		else
		{
			syncPosition = SyncMode::NONE;
		}
		// Same rotation logic.
		if (syncRotation != SyncMode::NONE)
		{
			if (sameVector(rotationLastFrame.Euler(), getRotation().Euler(), atRestRotationThreshold))
			{
				if (restStateRotation != RestState::AT_REST)
				{
					sameRotationCount += updatedDeltaTime;
				}

				if (sameRotationCount >= atRestThresholdCount)
				{
					sameRotationCount = 0;
					restStateRotation = RestState::AT_REST;
					forceStateSendNextFrame();
				}
			}
			else
			{
				if (restStateRotation == RestState::AT_REST && getRotation() != latestTeleportedFromRotation)
				{
					restStateRotation = RestState::JUST_STARTED_MOVING;
					forceStateSendNextFrame();
				}
				else if (restStateRotation == RestState::JUST_STARTED_MOVING)
				{
					restStateRotation = RestState::MOVING;
					//forceStateSendNextFixedUpdate();
				}
				else
				{
					sameRotationCount = 0;
				}
			}
		}
		else
		{
			syncRotation = SyncMode::NONE;
		}
	}

	// If Movement Mode (animation) has changed and nothing else has changed, send State regardless of when the last State was sent.
	sendMovementMode = shouldSendMovementMode();
	if (sendMovementMode)
	{
		forceStateSendNextFrame();
	}

	// If hasn't been long enough since the last send(and we aren't forcing a state send), return and don't send out.
	if (UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld()) - lastTimeStateWasSent < GetNetworkSendInterval() &&
		!forceStateSend) return;

	// Checks the core variables to see if we should be sending them out.
	sendPosition = shouldSendPosition();
	sendRotation = shouldSendRotation();
	sendScale = shouldSendScale();
	sendVelocity = shouldSendVelocity();
	sendAngularVelocity = shouldSendAngularVelocity();

	// Check that at least one variable has changed that we want to sync.
	if (!sendPosition && !sendRotation && !sendScale && !sendVelocity && !sendAngularVelocity && !sendMovementMode) return;

	sendingTempState->copyFromSmoothSync(this);

	// Check if should send rest messages.
	if (extrapolationMode != ExtrapolationMode::NONE)
	{
		if (restStatePosition == RestState::AT_REST) sendAtPositionalRestMessage = true;
		if (restStateRotation == RestState::AT_REST) sendAtRotationalRestMessage = true;

		// Send the new State when the object starts moving so we can interpolate correctly.
		if (restStatePosition == RestState::JUST_STARTED_MOVING)
		{
			sendingTempState->position = lastPositionWhenStateWasSent;
		}
		if (restStateRotation == RestState::JUST_STARTED_MOVING)
		{
			sendingTempState->rotation = lastRotationWhenStateWasSent;
		}
		if (restStatePosition == RestState::JUST_STARTED_MOVING ||
			restStateRotation == RestState::JUST_STARTED_MOVING)
		{
			sendingTempState->ownerTimestamp =
				UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld()) - GetOwner()->GetWorld()->GetDeltaSeconds();
			if (restStatePosition != RestState::JUST_STARTED_MOVING)
			{
				sendingTempState->position = positionLastFrame;
			}
			if (restStateRotation != RestState::JUST_STARTED_MOVING)
			{
				sendingTempState->rotation = rotationLastFrame;
			}
		}
	}
	lastTimeStateWasSent = UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld());

	SerializeState(sendingTempState);
}

void USmoothSync::resetFlags()
{
	forceStateSend = false;
	sendAtPositionalRestMessage = false;
	sendAtRotationalRestMessage = false;
}

void USmoothSync::SerializeState(SmoothState *sendingState)
{
	sendingCharArraySize = 0;
	sendingCharArray.Empty();

	if (sendPosition) lastPositionWhenStateWasSent = sendingState->position;
	if (sendRotation) lastRotationWhenStateWasSent = sendingState->rotation;
	if (sendScale) lastScaleWhenStateWasSent = sendingState->scale;
	if (sendVelocity) lastVelocityWhenStateWasSent = sendingState->velocity;
	if (sendAngularVelocity) lastAngularVelocityWhenStateWasSent = sendingState->angularVelocity;

	copyToBuffer(encodeSyncInformation(sendPosition, sendRotation, sendScale,
		sendVelocity, sendAngularVelocity, sendAtPositionalRestMessage, sendAtRotationalRestMessage, sendMovementMode));
	copyToBuffer(sendingState->ownerTimestamp);

	if (characterMovementComponent != nullptr)
	{
		if (sendMovementMode)
		{
			copyToBuffer(true);
			copyToBuffer(sendingState->movementMode);
			latestSentMovementMode = sendingState->movementMode;
		}
		else
		{
			copyToBuffer(false);
		}
	}

	// Write position.
	if (sendPosition)
	{
		if (isPositionCompressed)
		{
			// Divide by 100 before sending to make compression more accurate for larger numbers
			sendingState->position = sendingState->position / 100.0f;
			if (isSyncingXPosition())
			{
				copyToBuffer(FFloat16(sendingState->position.X));
			}
			if (isSyncingYPosition())
			{
				copyToBuffer(FFloat16(sendingState->position.Y));
			}
			if (isSyncingZPosition())
			{
				copyToBuffer(FFloat16(sendingState->position.Z));
			}
		}
		else
		{
			if (isSyncingXPosition())
			{
				copyToBuffer(sendingState->position.X);
			}
			if (isSyncingYPosition())
			{
				copyToBuffer(sendingState->position.Y);
			}
			if (isSyncingZPosition())
			{
				copyToBuffer(sendingState->position.Z);
			}
		}
	}
	// Write rotation.
	if (sendRotation)
	{
		FVector rot = sendingState->rotation.Euler();
		if (isRotationCompressed)
		{
			if (isSyncingXRotation())
			{
				copyToBuffer(FFloat16(rot.X));
			}
			if (isSyncingYRotation())
			{
				copyToBuffer(FFloat16(rot.Y));
			}
			if (isSyncingZRotation())
			{
				copyToBuffer(FFloat16(rot.Z));
			}
		}
		else
		{
			if (isSyncingXRotation())
			{
				copyToBuffer(rot.X);
			}
			if (isSyncingYRotation())
			{
				copyToBuffer(rot.Y);
			}
			if (isSyncingZRotation())
			{
				copyToBuffer(rot.Z);
			}
		}
	}
	// Write scale.
	if (sendScale)
	{
		if (isScaleCompressed)
		{
			if (isSyncingXScale())
			{
				copyToBuffer(FFloat16(sendingState->scale.X));
			}
			if (isSyncingYScale())
			{
				copyToBuffer(FFloat16(sendingState->scale.Y));
			}
			if (isSyncingZScale())
			{
				copyToBuffer(FFloat16(sendingState->scale.Z));
			}
		}
		else
		{
			if (isSyncingXScale())
			{
				copyToBuffer(sendingState->scale.X);
			}
			if (isSyncingYScale())
			{
				copyToBuffer(sendingState->scale.Y);
			}
			if (isSyncingZScale())
			{
				copyToBuffer(sendingState->scale.Z);
			}
		}
	}
	// Write velocity.
	if (sendVelocity)
	{
		if (isVelocityCompressed)
		{
			if (isSyncingXVelocity())
			{
				copyToBuffer(FFloat16(sendingState->velocity.X));
			}
			if (isSyncingYVelocity())
			{
				copyToBuffer(FFloat16(sendingState->velocity.Y));
			}
			if (isSyncingZVelocity())
			{
				copyToBuffer(FFloat16(sendingState->velocity.Z));
			}
		}
		else
		{
			if (isSyncingXVelocity())
			{
				copyToBuffer(sendingState->velocity.X);
			}
			if (isSyncingYVelocity())
			{
				copyToBuffer(sendingState->velocity.Y);
			}
			if (isSyncingZVelocity())
			{
				copyToBuffer(sendingState->velocity.Z);
			}
		}
	}
	// Write angular velocity.
	if (sendAngularVelocity)
	{
		if (isAngularVelocityCompressed)
		{
			if (isSyncingXAngularVelocity())
			{
				copyToBuffer(FFloat16(sendingState->angularVelocity.X));
			}
			if (isSyncingYAngularVelocity())
			{
				copyToBuffer(FFloat16(sendingState->angularVelocity.Y));
			}
			if (isSyncingZAngularVelocity())
			{
				copyToBuffer(FFloat16(sendingState->angularVelocity.Z));
			}
		}
		else
		{
			if (isSyncingXAngularVelocity())
			{
				copyToBuffer(sendingState->angularVelocity.X);
			}
			if (isSyncingYAngularVelocity())
			{
				copyToBuffer(sendingState->angularVelocity.Y);
			}
			if (isSyncingZAngularVelocity())
			{
				copyToBuffer(sendingState->angularVelocity.Z);
			}
		}
	}

	if (realObjectToSync->GetWorld()->IsServer())
	{
		ServerSendsTransformToEveryone(sendingCharArray);
	}
	else
	{
		ClientSendsTransformToServer(sendingCharArray);
	}
}
///// <summary>Use the SmoothState buffer to set interpolated or extrapolated Transforms and Rigidbodies on non-owned objects.</summary>
void USmoothSync::applyInterpolationOrExtrapolation()
{
	if (stateCount == 0) return;

	// Reset the temporary SmoothState so it can be refilled.
	if (!extrapolatedLastFrame)
	{
		targetTempState->defaultTheVariables();
	}

	triedToExtrapolateTooFar = false;

	bool isExtrapolating = false;

	// The target playback time
	float interpolationTime = getApproximateNetworkTimeOnOwner() - interpolationBackTime;

	// Use interpolation if the target playback time is present in the buffer.
	if (stateCount > 1 && stateBuffer[0]->ownerTimestamp > interpolationTime)
	{
		interpolate(interpolationTime, targetTempState);
		extrapolatedLastFrame = false;
	}
	// Don't extrapolate if we are at rest, but continue moving towards the final destination.
	else if (stateBuffer[0]->atPositionalRest && stateBuffer[0]->atRotationalRest)
	{
		targetTempState->copyFromState(stateBuffer[0]);
		extrapolatedLastFrame = false;
	}
	// The newest state is too old, we'll have to use extrapolation.
	else
	{
		bool success = extrapolate(interpolationTime, targetTempState);
		extrapolatedLastFrame = true;
		triedToExtrapolateTooFar = !success;
		if (!triedToExtrapolateTooFar)
		{
			isExtrapolating = true;
		}
	}

	float actualPositionLerpSpeed = positionLerpSpeed;
	float actualRotationLerpSpeed = rotationLerpSpeed;
	float actualScaleLerpSpeed = scaleLerpSpeed;

	if (dontLerp)
	{
		actualPositionLerpSpeed = 1;
		actualRotationLerpSpeed = 1;
		actualScaleLerpSpeed = 1;
		dontLerp = false;
	}

	// Set position, rotation, scale, velocity, and angular velocity (as long as we didn't try and extrapolate too far).
	if (!triedToExtrapolateTooFar)// || (!isSimulatingPhysics))
	{
		bool changedPositionEnough = false;
		float distance = 0;
		// If the current position is different from target position
		if (getPosition() != targetTempState->position)
		{
			// If we want to use either of these variables, we need to calculate the distance.
			if (positionSnapThreshold != 0 || receivedPositionThreshold != 0)
			{
				distance = FVector::Distance(getPosition(), targetTempState->position);
			}
		}
		// If we want to use receivedPositionThreshold, check if the distance has passed the threshold.
		if (receivedPositionThreshold != 0)
		{
			if (distance > receivedPositionThreshold)
			{
				changedPositionEnough = true;
			}
		}
		else // If we don't want to use receivedPositionThreshold, we will always set the new position.
		{
			changedPositionEnough = true;
		}

		bool changedRotationEnough = false;
		float angleDifference = 0;
		// If the current rotation is different from target rotation
		if (getRotation() != targetTempState->rotation)
		{
			// If we want to use either of these variables, we need to calculate the angle difference.
			if (rotationSnapThreshold != 0 || receivedRotationThreshold != 0)
			{
				if (realComponentToSync != NULL)
				{
					angleDifference = realComponentToSync->GetComponentRotation().Quaternion().AngularDistance(targetTempState->rotation);
				}
				else
				{
					angleDifference = realObjectToSync->GetActorRotation().Quaternion().AngularDistance(targetTempState->rotation);
				}
				angleDifference = angleDifference * (180.0f / PI);
			}
		}
		// If we want to use receivedRotationThreshold, check if the angle difference has passed the threshold.
		if (receivedRotationThreshold != 0)
		{
			if (angleDifference > receivedRotationThreshold)
			{
				changedRotationEnough = true;
			}
		}
		else // If we don't want to use receivedRotationThreshold, we will always set the new position.
		{
			changedRotationEnough = true;
		}

		bool changedScaleEnough = false;
		float scaleDistance = 0;
		// If current scale is different from target scale
		if (getScale() != targetTempState->scale)
		{
			changedScaleEnough = true;
			// If we want to use scaleSnapThreshhold, calculate the distance.
			if (scaleSnapThreshold != 0)
			{
				scaleDistance = FVector::Distance(getScale(), targetTempState->scale);
			}
		}

		// Set velocity to zero so it doesn't affect our Smooth movement
		if (isSimulatingPhysics && !isExtrapolating)
		{
			setLinearVelocity(FVector::ZeroVector);
			setAngularVelocity(FVector::ZeroVector);
		}

		if (syncPosition != SyncMode::NONE && !isExtrapolating)
		{
			if (changedPositionEnough)
			{
				bool shouldTeleport = false;
				if (distance > positionSnapThreshold)
				{
					actualPositionLerpSpeed = 1;
					shouldTeleport = true;
				}
				FVector newPosition = getPosition();
				if (isSyncingXPosition())
				{
					newPosition.X = targetTempState->position.X;
				}
				if (isSyncingYPosition())
				{
					newPosition.Y = targetTempState->position.Y;
				}
				if (isSyncingZPosition())
				{
					newPosition.Z = targetTempState->position.Z;
				}
				setPosition(FMath::Lerp(getPosition(), newPosition, actualPositionLerpSpeed));
			}
		}
		if (syncRotation != SyncMode::NONE && !isExtrapolating)
		{
			if (changedRotationEnough)
			{
				bool shouldTeleport = false;
				if (angleDifference > rotationSnapThreshold)
				{
					actualRotationLerpSpeed = 1;
					shouldTeleport = true;
				}
				FVector newRotation = getRotation().Euler();
				if (isSyncingXRotation())
				{
					newRotation.X = targetTempState->rotation.Euler().X;
				}
				if (isSyncingYRotation())
				{
					newRotation.Y = targetTempState->rotation.Euler().Y;
				}
				if (isSyncingZRotation())
				{
					newRotation.Z = targetTempState->rotation.Euler().Z;
				}
				FQuat newQuaternion = FQuat::MakeFromEuler(newRotation);
				setRotation(FMath::Lerp(getRotation(), newQuaternion, actualRotationLerpSpeed));
			}
		}
		if (syncScale != SyncMode::NONE)
		{
			if (changedScaleEnough)
			{
				bool shouldTeleport = false;
				if (scaleDistance > scaleSnapThreshold)
				{
					actualScaleLerpSpeed = 1;
					shouldTeleport = true;
				}
				FVector newScale = getScale();
				if (isSyncingXScale())
				{
					newScale.X = targetTempState->scale.X;
				}
				if (isSyncingYScale())
				{
					newScale.Y = targetTempState->scale.Y;
				}
				if (isSyncingZScale())
				{
					newScale.Z = targetTempState->scale.Z;
				}
				setScale(FMath::Lerp(getScale(), newScale, actualScaleLerpSpeed));
			}
		}
	}
	else if (triedToExtrapolateTooFar)
	{
		if (isSimulatingPhysics)
		{
			setLinearVelocity(FVector::ZeroVector);
			setAngularVelocity(FVector::ZeroVector);
		}
	}
	if (characterMovementComponent != nullptr)
	{
		setLinearVelocity(targetTempState->velocity);
		characterMovementComponent->ApplyNetworkMovementMode(targetTempState->movementMode);
	}
}

/// <summary>
/// Interpolate between two States from the stateBuffer in order calculate the targetState.
/// </summary>
/// <param name="interpolationTime">The target time</param>
void USmoothSync::interpolate(float interpolationTime, SmoothState *targetState)
{
	// Go through buffer and find correct SmoothState to start at.
	int stateIndex = 0;
	for (; stateIndex < stateCount; stateIndex++)
	{
		if (stateBuffer[stateIndex]->ownerTimestamp <= interpolationTime) break;
	}

	if (stateIndex == stateCount)
	{
		//Debug.LogError("Ran out of States in SmoothSync SmoothState buffer for object: " + gameObject.name);
		stateIndex--;
	}

	// The SmoothState one slot newer than the starting SmoothState.
	SmoothState *end = stateBuffer[FMath::Max(stateIndex - 1, 0)];
	// The starting playback SmoothState.
	SmoothState *start = stateBuffer[stateIndex];

	// Calculate how far between the two States we should be.
	float t = (interpolationTime - start->ownerTimestamp) / (end->ownerTimestamp - start->ownerTimestamp);

	shouldTeleport(start, end, interpolationTime, &t);

	// Interpolate between the States to get the target SmoothState.
	targetState->Lerp(targetState, start, end, t);
}

/// <summary>
/// Attempt to extrapolate from the newest SmoothState in the buffer
/// </summary>
/// <param name="interpolationTime">The target time</param>
/// <returns>true on success, false if interpolationTime is more than extrapolationLength in the future</returns>
bool USmoothSync::extrapolate(float interpolationTime, SmoothState *targetState) // TODO: Wouldn't it make sense to at least extrapolate up to extrapolation limit even when it's trying to extrapolate too far?
{
	// Start from the latest State
	if (!extrapolatedLastFrame || targetState->ownerTimestamp < stateBuffer[0]->ownerTimestamp)
	{
		targetState->copyFromState(stateBuffer[0]);
		timeSpentExtrapolating = 0;
	}

	// If we don't want to extrapolate, don't.
	if (extrapolationMode == ExtrapolationMode::NONE) return false;

	// Determines velocities based on previous State. Used on non-rigidbodies and when not syncing velocity 
	// to save bandwidth. This is less accurate than syncing velocity for rigidbodies. 
	if (extrapolationMode != ExtrapolationMode::NONE && stateCount >= 2)
	{
		if (syncVelocity == SyncMode::NONE && !stateBuffer[0]->atPositionalRest)
		{
			targetState->velocity = (stateBuffer[0]->position - stateBuffer[1]->position) / (stateBuffer[0]->ownerTimestamp - stateBuffer[1]->ownerTimestamp);
		}
		if (syncAngularVelocity == SyncMode::NONE && !stateBuffer[0]->atRotationalRest)
		{
			FQuat deltaRot = stateBuffer[0]->rotation * stateBuffer[1]->rotation.Inverse();
			float x = FMath::FindDeltaAngleDegrees(0, deltaRot.Euler().X);
			float y = FMath::FindDeltaAngleDegrees(0, deltaRot.Euler().Y);
			float z = FMath::FindDeltaAngleDegrees(0, deltaRot.Euler().Z);
			FVector eulerRot = FVector(x, y, z);
			FVector angularVelocity = eulerRot / (stateBuffer[0]->ownerTimestamp - stateBuffer[1]->ownerTimestamp);
			targetState->angularVelocity = angularVelocity;
		}
	}

	// Don't extrapolate for more than extrapolationTimeLimit if we are using it.
	if (useExtrapolationTimeLimit &&
		timeSpentExtrapolating > extrapolationTimeLimit)
	{
		return false;
	}

	// Set up some booleans for if we are moving.
	bool hasVelocity = FMath::Abs(targetState->velocity.X) >= .01f || FMath::Abs(targetState->velocity.Y) >= .01f ||
		FMath::Abs(targetState->velocity.Z) >= .01f;
	bool hasAngularVelocity = FMath::Abs(targetState->angularVelocity.X) >= .01f || FMath::Abs(targetState->angularVelocity.Y) >= .01f ||
		FMath::Abs(targetState->angularVelocity.Z) >= .01f;

	// If not moving, don't extrapolate. This is so we don't try to extrapolate while at rest.
	if (!hasVelocity && !hasAngularVelocity)
	{
		return false;
	}

	// Calculate how long to extrapolate from the current target State.
	float timeDif = 0;
	if (timeSpentExtrapolating == 0)
	{
		timeDif = interpolationTime - targetState->ownerTimestamp;
	}
	else
	{
		timeDif = updatedDeltaTime;
	}
	timeSpentExtrapolating += timeDif;

	//// See how far we will need to extrapolate.
	//float extrapolationLength = (interpolationTime - targetState->ownerTimestamp) / 1000.0f;

	//// If latest received velocity is close to zero, don't extrapolate. This is so we don't
	//// try to extrapolate through the ground while at rest.
	//if (deserializeVelocity == SyncMode::NONE || targetState->velocity.Size() < sendVelocityThreshold)
	//{
	//	return true;
	//}

	// Only extrapolate position if enabled and not at positional rest.
	if (hasVelocity && isSimulatingPhysics)
	{
		// Velocity.
		setLinearVelocity(targetState->velocity);

		// Drag.
		targetState->velocity -= targetState->velocity * timeDif * primitiveComponent->GetLinearDamping();
	}

	// Only extrapolate rotation if enabled and not at rotational rest.
	if (hasAngularVelocity && isSimulatingPhysics)
	{
		setAngularVelocity(targetState->angularVelocity);

		// Angular drag.
		targetState->angularVelocity -= targetState->angularVelocity * timeDif * primitiveComponent->GetAngularDamping();
	}

	// Don't extrapolate for more than extrapolationDistanceLimit if we are using it.
	if (useExtrapolationDistanceLimit &&
		FVector::Distance(stateBuffer[0]->position, targetState->position) >= extrapolationDistanceLimit)
	{
		return false;
	}

	return true;
}
void USmoothSync::shouldTeleport(SmoothState *start, SmoothState *end, float interpolationTime, float *t)
{
	// If the interpolationTime is further back than the start State time and start State is a teleport, then teleport.
	if (start->ownerTimestamp > interpolationTime && start->teleport && stateCount == 2)
	{
		// Because we are further back than the Start state, the Start state is our end State.
		end = start;
		*t = 1;
		stopLerping();
	}
	// Check if low FPS caused us to skip a teleport State. If yes, teleport.
	for (int i = 0; i < stateCount; i++)
	{
		if (stateBuffer[i] == latestEndStateUsed && latestEndStateUsed != end && latestEndStateUsed != start)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (stateBuffer[j]->teleport == true)
				{
					*t = 1;
					stopLerping();
				}
				if (stateBuffer[j] == start) break;
			}
			break;
		}
	}
	latestEndStateUsed = end;
	// If target State is a teleport State, stop lerping and immediately move to it.
	if (end->teleport == true)
	{
		*t = 1;
		stopLerping();
	}
}

/// <summary>Get position of object.</summary>
FVector USmoothSync::getPosition()
{
	if (realComponentToSync != NULL)
	{
		return realComponentToSync->RelativeLocation;
	}
	else if (realObjectToSync->GetAttachParentActor())
	{
		return realObjectToSync->GetTransform().GetRelativeTransform(realObjectToSync->GetAttachParentActor()->GetActorTransform()).GetLocation();
	}
	else
	{
		return realObjectToSync->GetActorLocation();
	}
}
/// <summary>Get rotation of object.</summary>
FQuat USmoothSync::getRotation()
{
	if (realComponentToSync != NULL)
	{
		return realComponentToSync->GetComponentQuat();
	}
	else if (realObjectToSync->GetAttachParentActor())
	{
		return realObjectToSync->GetTransform().GetRelativeTransform(realObjectToSync->GetAttachParentActor()->GetActorTransform()).GetRotation();
	}
	else
	{
		return realObjectToSync->GetActorQuat();
	}
}
/// <summary>Get scale of object.</summary>
FVector USmoothSync::getScale()
{
	if (realComponentToSync != NULL)
	{
		return realComponentToSync->RelativeScale3D;
	}
	else
	{
		return realObjectToSync->GetActorRelativeScale3D();
	}
}
/// <summary>Set scale of object.</summary>
FVector USmoothSync::getLinearVelocity()
{
	if (isSimulatingPhysics)
	{
		return primitiveComponent->GetPhysicsLinearVelocity();
	}
	else if (movementComponent != nullptr)
	{
		return movementComponent->Velocity;
	}
	else if (characterMovementComponent != nullptr)
	{
		return characterMovementComponent->Velocity;
	}
	else
	{
		return FVector::ZeroVector;
	}
}
/// <summary>Set scale of object.</summary>
FVector USmoothSync::getAngularVelocity()
{
	return primitiveComponent->GetPhysicsAngularVelocityInDegrees();
}
/// <summary>Set position of object.</summary>
void USmoothSync::setPosition(FVector position)
{
	if (realComponentToSync != NULL)
	{
		realComponentToSync->SetRelativeLocation(position, false, 0, ETeleportType::TeleportPhysics);
	}
	else if (realObjectToSync->GetAttachParentActor())
	{
		realObjectToSync->SetActorRelativeLocation(position, false, 0, ETeleportType::TeleportPhysics);
	}
	else
	{
		realObjectToSync->SetActorLocation(position, false, 0, ETeleportType::TeleportPhysics);
	}
}
/// <summary>Set rotation of object.</summary>
void USmoothSync::setRotation(const FQuat &rotation)
{
	if (realComponentToSync != NULL)
	{
		realComponentToSync->SetWorldRotation(rotation, false, NULL, ETeleportType::TeleportPhysics);//->SetRelativeRotation(rotation);
	}
	else if (realObjectToSync->GetAttachParentActor())
	{
		realObjectToSync->SetActorRelativeRotation(rotation, false, NULL, ETeleportType::TeleportPhysics);
	}
	else
	{
		realObjectToSync->SetActorRotation(rotation, ETeleportType::TeleportPhysics);
	}
}
/// <summary>Set scale of object.</summary>
void USmoothSync::setScale(FVector scale)
{
	if (realComponentToSync != NULL)
	{
		realComponentToSync->SetRelativeScale3D(scale);
	}
	else
	{
		realObjectToSync->SetActorRelativeScale3D(scale);
	}
}
/// <summary>Set scale of object.</summary>
void USmoothSync::setLinearVelocity(FVector linearVelocity)
{
	if (isSimulatingPhysics)
	{
		primitiveComponent->SetPhysicsLinearVelocity(FVector(linearVelocity));
	}
	else if (movementComponent != nullptr)
	{
		movementComponent->Velocity = linearVelocity;
	}
	else if (characterMovementComponent != nullptr)
	{
		characterMovementComponent->Velocity = linearVelocity;
	}
}
/// <summary>Set scale of object.</summary>
void USmoothSync::setAngularVelocity(FVector angularVelocity)
{
	if (isSimulatingPhysics)
	{
		primitiveComponent->SetPhysicsAngularVelocityInDegrees(FVector(angularVelocity));
	}
}

//#endregion Internal stuff

//#region Public interface

/// <summary>Add an incoming state to the stateBuffer on non-owned objects.</summary>
void USmoothSync::addState(SmoothState *state)
{
	if (stateCount > 1 && state->ownerTimestamp <= stateBuffer[0]->ownerTimestamp)
	{
		// This state arrived out of order and we already have a newer state.
		//UE_LOG(LogTemp, Warning, TEXT("Received state out of order for"));
		return;
	}

	if (UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld()) - lastTimeStateWasReceived > receiveSnapTimeThreshold * 5.0f)
	{
		_ownerTime = state->ownerTimestamp;
		lastTimeOwnerTimeWasSet = UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld());
	}

	lastTimeStateWasReceived = UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld());

	// Shift the buffer
	int stateBufferLength = std::max(calculatedStateBufferSize, 30);
	if (stateBuffer[stateBufferLength - 1] != NULL)
	{
		delete stateBuffer[stateBufferLength - 1];
	}
	for (int i = stateBufferLength - 1; i >= 1; i--)
	{
		stateBuffer[i] = stateBuffer[i - 1];
	}

	// Add the new SmoothState at the front of the buffer.
	stateBuffer[0] = state;

	// Keep track of how many States are in the buffer.	
	stateCount = FMath::Min(stateCount + 1, stateBufferLength);
}

/// <summary>Stop updating the States of non-owned objects so that the object can be teleported.</summary>
void USmoothSync::stopLerping()
{
	dontLerp = true;
}

/// <summary>Effectively clear the state buffer. Used for teleporting and ownership changes.</summary>
void USmoothSync::clearBuffer()
{
	stateCount = 0;
}

/// <summary>
/// Teleport the player so that position will not be interpolated on non-owners.
/// </summary>
/// <remarks>
/// Use teleport() on the owner and the Actor will jump to the current owner's position on non-owners. 
/// </remarks>
void USmoothSync::teleport()
{
	if (!shouldSendTransform())
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to teleport from an unowned object. You can only teleport from an owned object. Look up Unreal networking object ownership."));
		return;
	}
	latestTeleportedFromPosition = getPosition();
	latestTeleportedFromRotation = getRotation();
	if (realObjectToSync->GetWorld()->IsServer())
	{
		SmoothSyncTeleportServerToClients(getPosition(), getRotation().Euler(), getScale(),
			UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld()));
	}
	else
	{
		SmoothSyncTeleportClientToServer(getPosition(), getRotation().Euler(), getScale(),
			UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld()));
	}
}
/// <summary>
/// Add the teleport State at the correct place in the State buffer.
/// </summary>
void USmoothSync::addTeleportState(SmoothState *teleportState)
{
	int stateBufferLength = std::max(calculatedStateBufferSize, 30);

	// If the teleport State is the newest received State.
	if (stateCount == 0 || teleportState->ownerTimestamp >= stateBuffer[0]->ownerTimestamp)
	{
		// Shift the buffer, deleting the oldest State.
		for (int k = stateBufferLength - 1; k >= 1; k--)
		{
			stateBuffer[k] = stateBuffer[k - 1];
		}
		// Add the new State at the front of the buffer.
		stateBuffer[0] = teleportState;

		// Fix for if the first received State is a teleport.
		if (stateCount == 0)
		{
			SmoothState *newTeleportState = new SmoothState();
			newTeleportState->copyFromState(teleportState);
			stateBuffer[1] = newTeleportState;
			stateCount = FMath::Min(stateCount + 1, stateBufferLength);
		}
	}
	// Check the rest of the States to see where the teleport State belongs.
	else
	{
		for (int i = stateBufferLength - 2; i >= 0; i--)
		{
			if (stateBuffer[i]->ownerTimestamp > teleportState->ownerTimestamp)
			{
				// Shift the buffer from where the teleport State should be and add the new State. 
				for (int j = stateBufferLength - 1; j >= 1; j--)
				{
					if (j == i) break;
					stateBuffer[j] = stateBuffer[j - 1];
				}
				stateBuffer[i + 1] = teleportState;
				break;
			}
		}
	}
	// Keep track of how many States are in the buffer.
	stateCount = FMath::Min(stateCount + 1, stateBufferLength);
}
/// <summary>
/// Forces the SmoothState to be sent on owned objects the next time it goes through Update().
/// </summary>
/// <remarks>
/// The SmoothState will get sent next frame regardless of all limitations.
/// </remarks>
void USmoothSync::forceStateSendNextFrame()
{
	forceStateSend = true;
}

bool USmoothSync::sameVector(FVector one, FVector two, float threshold)
{
	if (FMath::Abs(one.X - two.X) > threshold) return false;
	if (FMath::Abs(one.Y - two.Y) > threshold) return false;
	if (FMath::Abs(one.Z - two.Z) > threshold) return false;
	return true;
}
/// <summary>
/// Check if position has changed enough.
/// </summary>
/// <remarks>
/// If sendPositionThreshold is 0, returns true if the current position is different than the latest sent position.
/// If sendPositionThreshold is greater than 0, returns true if distance between position and latest sent position is greater 
/// than the sendPositionThreshold.
/// </remarks>
bool USmoothSync::shouldSendPosition()
{
	if (syncPosition != SyncMode::NONE &&
		(forceStateSend ||
		(!sameVector(getPosition(), lastPositionWhenStateWasSent, sendPositionThreshold) &&
			restStatePosition != RestState::AT_REST)))
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Check if rotation has changed enough.
/// </summary>
/// <remarks>
/// If sendRotationThreshold is 0, returns true if the current rotation is different from the latest sent rotation.
/// If sendRotationThreshold is greater than 0, returns true if difference (angle) between rotation and latest sent rotation is greater 
/// than the sendRotationThreshold.
/// </remarks>
bool USmoothSync::shouldSendRotation()
{
	if (syncRotation != SyncMode::NONE &&
		(forceStateSend ||
		(!sameVector(getRotation().Euler(), lastRotationWhenStateWasSent.Euler(), sendRotationThreshold) &&
			restStateRotation != RestState::AT_REST)))
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Check if scale has changed enough.
/// </summary>
/// <remarks>
/// If sendScaleThreshold is 0, returns true if the current scale is different than the latest sent scale.
/// If sendScaleThreshold is greater than 0, returns true if the difference between scale and latest sent scale is greater 
/// than the sendScaleThreshold.
/// </remarks>
bool USmoothSync::shouldSendScale()
{
	if (syncScale != SyncMode::NONE &&
		(forceStateSend ||
		(!sameVector(getScale(), lastScaleWhenStateWasSent, sendScaleThreshold) &&
			(sendScaleThreshold == 0 || FVector::Distance(lastScaleWhenStateWasSent, getScale()) > sendScaleThreshold))))
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Check if velocity has changed enough.
/// </summary>
/// <remarks>
/// If sendVelocityThreshold is 0, returns true if the current velocity is different from the latest sent velocity.
/// If sendVelocityThreshold is greater than 0, returns true if difference between velocity and latest sent velocity is greater 
/// than the velocity threshold.
/// </remarks>
bool USmoothSync::shouldSendVelocity()
{
	if (isSimulatingPhysics || characterMovementComponent != nullptr || movementComponent != nullptr)
	{
		if (syncVelocity != SyncMode::NONE &&
			(forceStateSend ||
			(!sameVector(getLinearVelocity(), lastVelocityWhenStateWasSent, sendVelocityThreshold) &&
				restStatePosition != RestState::AT_REST)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Check if angular velocity has changed enough.
/// </summary>
/// <remarks>
/// If sendAngularVelocityThreshold is 0, returns true if the current angular velocity is different from the latest sent angular velocity.
/// If sendAngularVelocityThreshold is greater than 0, returns true if difference between angular velocity and latest sent angular velocity is 
/// greater than the angular velocity threshold.
/// </remarks>
bool USmoothSync::shouldSendAngularVelocity()
{
	if (isSimulatingPhysics)
	{
		if (syncAngularVelocity != SyncMode::NONE &&
			(forceStateSend ||
			(!sameVector(getAngularVelocity(), lastAngularVelocityWhenStateWasSent, sendAngularVelocityThreshold) &&
				restStateRotation != RestState::AT_REST)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Check if we want to sync Movement Mode and if it has changed.
/// </summary>
bool USmoothSync::shouldSendMovementMode()
{
	if (syncMovementMode &&
		characterMovementComponent != nullptr &&
		latestSentMovementMode != characterMovementComponent->MovementMode)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//#region Sync Properties
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingXPosition()
{
	if (syncPosition == SyncMode::XYZ ||
		syncPosition == SyncMode::XY ||
		syncPosition == SyncMode::XZ ||
		syncPosition == SyncMode::X)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingYPosition()
{
	if (syncPosition == SyncMode::XYZ ||
		syncPosition == SyncMode::XY ||
		syncPosition == SyncMode::YZ ||
		syncPosition == SyncMode::Y)
	{
		return true;
	}
	else
	{
		return false;
	}

}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingZPosition()
{
	if (syncPosition == SyncMode::XYZ ||
		syncPosition == SyncMode::XZ ||
		syncPosition == SyncMode::YZ ||
		syncPosition == SyncMode::Z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingXRotation()
{
	if (syncRotation == SyncMode::XYZ ||
		syncRotation == SyncMode::XY ||
		syncRotation == SyncMode::XZ ||
		syncRotation == SyncMode::X)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingYRotation()
{
	if (syncRotation == SyncMode::XYZ ||
		syncRotation == SyncMode::XY ||
		syncRotation == SyncMode::YZ ||
		syncRotation == SyncMode::Y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingZRotation()
{
	if (syncRotation == SyncMode::XYZ ||
		syncRotation == SyncMode::XZ ||
		syncRotation == SyncMode::YZ ||
		syncRotation == SyncMode::Z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingXScale()
{
	if (syncScale == SyncMode::XYZ ||
		syncScale == SyncMode::XY ||
		syncScale == SyncMode::XZ ||
		syncScale == SyncMode::X)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingYScale()
{
	if (syncScale == SyncMode::XYZ ||
		syncScale == SyncMode::XY ||
		syncScale == SyncMode::YZ ||
		syncScale == SyncMode::Y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingZScale()
{
	if (syncScale == SyncMode::XYZ ||
		syncScale == SyncMode::XZ ||
		syncScale == SyncMode::YZ ||
		syncScale == SyncMode::Z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingXVelocity()
{
	if (syncVelocity == SyncMode::XYZ ||
		syncVelocity == SyncMode::XY ||
		syncVelocity == SyncMode::XZ ||
		syncVelocity == SyncMode::X)
	{
		return true;
	}
	else
	{
		return false;
	}

}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingYVelocity()
{
	if (syncVelocity == SyncMode::XYZ ||
		syncVelocity == SyncMode::XY ||
		syncVelocity == SyncMode::YZ ||
		syncVelocity == SyncMode::Y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingZVelocity()
{
	if (syncVelocity == SyncMode::XYZ ||
		syncVelocity == SyncMode::XZ ||
		syncVelocity == SyncMode::YZ ||
		syncVelocity == SyncMode::Z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingXAngularVelocity()
{
	if (syncAngularVelocity == SyncMode::XYZ ||
		syncAngularVelocity == SyncMode::XY ||
		syncAngularVelocity == SyncMode::XZ ||
		syncAngularVelocity == SyncMode::X)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingYAngularVelocity()
{
	if (syncAngularVelocity == SyncMode::XYZ ||
		syncAngularVelocity == SyncMode::XY ||
		syncAngularVelocity == SyncMode::YZ ||
		syncAngularVelocity == SyncMode::Y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// Determine if should be syncing.
/// </summary>
bool USmoothSync::isSyncingZAngularVelocity()
{
	if (syncAngularVelocity == SyncMode::XYZ ||
		syncAngularVelocity == SyncMode::XZ ||
		syncAngularVelocity == SyncMode::YZ ||
		syncAngularVelocity == SyncMode::Z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float USmoothSync::GetNetworkSendInterval()
{
	return 1 / sendRate;
}

/// <summary>
/// The current estimated time on the owner.
/// </summary>
/// <remarks>
/// Time comes from the owner in every sync message.
/// When it is received we set _ownerTime and lastTimeOwnerTimeWasSet.
/// </remarks>
float USmoothSync::getApproximateNetworkTimeOnOwner()
{
	return _ownerTime + (UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld()) - lastTimeOwnerTimeWasSet);
}


/// <summary>
/// Adjust owner time based on latest timestamp.
/// </summary>
void USmoothSync::adjustOwnerTime()
{
	// Don't adjust time if at rest or no state received yet.
	if (stateBuffer[0] == NULL || (stateBuffer[0]->atPositionalRest && stateBuffer[0]->atRotationalRest)) return;

	float newTime = stateBuffer[0]->ownerTimestamp + (UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld()) - lastTimeStateWasReceived);
	float timeCorrection = (timeCorrectionSpeed + 1.0f) * updatedDeltaTime;
	float timeChangeMagnitude = FMath::Abs(getApproximateNetworkTimeOnOwner() - newTime);

	if (_ownerTime == 0)
	{
		_ownerTime = stateBuffer[0]->ownerTimestamp;
		lastTimeOwnerTimeWasSet = UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld());
	}

	if ((receivedStatesCounter < sendRate * .7f) ||
		timeChangeMagnitude < timeCorrection ||
		timeChangeMagnitude > snapTimeThreshold)
	{
		_ownerTime = newTime;
		lastTimeOwnerTimeWasSet = UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld());
	}
	else
	{
		if (getApproximateNetworkTimeOnOwner() < newTime)
		{
			_ownerTime += timeCorrection;
			lastTimeOwnerTimeWasSet = UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld());
		}
		else
		{
			_ownerTime -= timeCorrection;
			lastTimeOwnerTimeWasSet = UGameplayStatics::GetRealTimeSeconds(GetOwner()->GetWorld());
		}
	}
}