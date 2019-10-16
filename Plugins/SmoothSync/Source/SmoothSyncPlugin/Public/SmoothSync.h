// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include <algorithm>    // std::max
#include "Runtime/Engine/Classes/GameFramework/MovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "SmoothSync.generated.h"


class SmoothState;
class NetworkState;


/// <summary>The variables that will be synced.</summary>
UENUM(BlueprintType)
enum class SyncMode : uint8
{
	XYZ, XY, XZ, YZ, X, Y, Z, NONE
};

/// <summary>The extrapolation mode.</summary>
UENUM(BlueprintType)
enum class ExtrapolationMode : uint8
{
	UNLIMITED, LIMITED, NONE
};
/// <summary>The variables that will be synced.</summary>
UENUM(BlueprintType)
enum class RestState : uint8
{
	AT_REST, JUST_STARTED_MOVING, MOVING
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SMOOTHSYNCPLUGIN_API USmoothSync : public UActorComponent
{
	GENERATED_BODY()


		TArray<uint8> sendingCharArray;
	int sendingCharArraySize = 0;
	TArray<uint8> readingCharArray;
	int readingCharArraySize = 0;

public:
	/// Sets default values for this component's properties
	USmoothSync();

	/// <summary>How much time in the past non-owned objects should be.</summary>
	/// <remarks>
	/// interpolationBackTime is the amount of time in the past the object will be on non-owners.
	/// This is so if you hit a latency spike, you still have a buffer of the interpolation back time of known States 
	/// before you start extrapolating into the unknown.
	///
	/// Increasing will make interpolation more likely to be used,
	/// which means the synced position will be more likely to be an actual position that the owner was at.
	///
	/// Decreasing will make extrapolation more likely to be used,
	/// this will increase reponsiveness, but with any latency spikes that last longer than the interpolationBackTime, 
	/// the position will be less correct to where the player was actually at.
	///
	/// Keep this higher than 1/SendRate to attempt to always interpolate. Keep in mind your send rate may fluctuate
	/// depending on your Unreal NetpdateFrequency settings and NetPriority. 
	///  
	/// Measured in seconds.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Important)
		float interpolationBackTime = .1f;
	/// <summary>The amount of extrapolation used.</summary>
	/// <remarks>
	/// Extrapolation is going into the unknown based on information we had in the past. Generally, you'll
	/// want extrapolation to help fill in missing information during lag spikes. 
	/// None - Use no extrapolation. 
	/// Limited - Use the settings for extrapolation limits. 
	/// Unlimited - Allow extrapolation forever. 
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extrapolation)
		ExtrapolationMode extrapolationMode = ExtrapolationMode::LIMITED;
	/// <summary>Whether or not to have an extrapolation time limit.</summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extrapolation)
		bool useExtrapolationTimeLimit = true;
	/// <summary>How much time into the future a non-owned object is allowed to extrapolate.</summary>
	/// <remarks>
	/// Extrapolating too far tends to cause erratic and non-realistic movement, but a little bit of extrapolation is 
	/// better than none because it keeps things working semi-right during latency spikes.
	///
	/// Measured in seconds.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extrapolation)
		float extrapolationTimeLimit = 1.0f;
	/// <summary>Whether or not to have an extrapolation distance limit.</summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extrapolation)
		bool useExtrapolationDistanceLimit;

	/// <summary>How much distance into the future a non-owned object is allowed to extrapolate.</summary>
	/// <remarks>
	/// Extrapolating too far tends to cause erratic and non-realistic movement, but a little bit of extrapolation is 
	/// better than none because it keeps things working semi-right during latency spikes.
	/// 
	/// Measured in distance units.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extrapolation)
		float extrapolationDistanceLimit = 100.0f;

	/// <summary>The position won't send unless one of its Vector values has changed this much.</summary>
	/// <remarks>
	/// Set to 0 to send the position of owned objects if it has changed since the last sent position.
	/// Will not send quicker than SendRate.
	///
	/// If greater than 0, a synced object's position is only sent if its vector position value is off from the last
	/// sent position by more than the threshold. 
	///
	/// Measured in distance units.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float sendPositionThreshold = 0.0f;

	/// <summary>The rotation won't send unless one of its Vector values has changed this much.</summary>
	/// <remarks>
	/// Set to 0 to send the rotation of owned objects if it has changed since the last sent rotation.
	/// Will not send quicker than SendRate.
	///
	/// If greater than 0, a synced object's rotation is only sent if its euler value is off from the last sent rotation
	/// by more than the threshold.
	///
	/// Measured in degrees.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float sendRotationThreshold = 0.0f;

	/// <summary>The scale won't send unless one of its Vector values it changed this much.</summary>
	/// <remarks>
	/// Set to 0 to send the scale of owned objects if it has changed since the last sent scale.
	/// Will not send quicker than SendRate.
	///
	/// If greater than 0, a synced object's scale is only sent if its scale is off from the last sent scale by more 
	/// than the threshold. 
	///
	/// Measured in distance units.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float sendScaleThreshold = 0.0f;

	/// <summary>The velocity won't send unless one of its Vector values changed this much.</summary>
	/// <remarks>
	/// Set to 0 to send the velocity of owned objects if it has changed since the last sent velocity.
	/// Will not send quicker than SendRate.
	///
	/// If greater than 0, a synced object's velocity is only sent if its velocity is off from the last sent velocity
	/// by more than the threshold. 
	///
	/// Measured in velocity units.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float sendVelocityThreshold = 0.0f;

	/// <summary>The angular velocity won't send unless one of its Vector values changed this much.</summary>
	/// <remarks>
	/// Set to 0 to send the angular velocity of owned objects if it has changed since the last sent angular velocity.
	/// Will not send quicker than SendRate.
	///
	/// If greater than 0, a synced object's angular velocity is only sent if its angular velocity is off from the last sent angular velocity
	/// by more than the threshold. 
	///
	/// Measured in radians per second.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float sendAngularVelocityThreshold = 0.0f;

	/// <summary>The position won't be set on non-owned objects unless it changed this much.</summary>
	/// <remarks>
	/// Set to 0 to always update the position of non-owned objects if it has changed, and to use one less distance check per frame if you also have positionSnapThreshold at 0.
	/// If greater than 0, a synced object's position is only updated if it is off from the target position by more than the threshold.
	///
	/// Usually keep this at 0 or really low, at higher numbers it's useful if you are extrapolating into the future and want to stop instantly 
	/// and not have it backtrack to where it currently is on the owner.
	///
	/// Measured in distance units.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float receivedPositionThreshold = 0.0f;

	/// <summary>The rotation won't be set on non-owned objects unless it changed this much.</summary>
	/// <remarks>
	/// Set to 0 to always update the rotation of non-owned objects if it has changed, and to use one less FQuat.AngularDistance() check per frame if you also have rotationSnapThreshold at 0.
	/// If greater than 0, a synced object's rotation is only updated if it is off from the target rotation by more than the threshold.
	///
	/// Usually keep this at 0 or really low, at higher numbers it's useful if you are extrapolating into the future and want to stop instantly and 
	/// not have it backtrack to where it currently is on the owner.
	///
	/// Measured in degrees.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float receivedRotationThreshold = 0.0f;

	/// <summary>If a synced object's position is more than positionSnapThreshold units from the target position, it will jump to the target position immediately instead of lerping.</summary>
	/// <remarks>
	/// Set to zero to not use at all and use one less distance check per frame if you also have receivedPositionThreshold at 0.
	///
	/// Measured in distance units.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float positionSnapThreshold = 500;

	/// <summary>If a synced object's rotation is more than rotationSnapThreshold from the target rotation, it will jump to the target rotation immediately instead of lerping.</summary>
	/// <remarks>
	/// Set to zero to not use at all and use one less FQuat.AnglularDistance() check per frame if you also have receivedRotationThreshold at 0.
	///
	/// Measured in degrees.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float rotationSnapThreshold = 100;

	/// <summary>If a synced object's scale is more than scaleSnapThreshold units from the target scale, it will jump to the target scale immediately instead of lerping.</summary>
	/// <remarks>
	/// Set to zero to not use at all and use one less distance check per frame.
	///
	/// Measured in distance units.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float scaleSnapThreshold = 3;

	/// <summary>How fast to change the estimated owner time of non-owned objects. 0 is never, 5 is basically instant.</summary>
	/// <remarks>
	/// The estimated owner time will shift by at most this amount per second. Lower values will be smoother but it may take a bit 
	/// to adjust to larger jumps in latency. Probably keep this lower than ~.6 unless you are having serious latency variance issues. 
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Important, meta = (ClampMin = "0.0", ClampMax = "5.0", UIMin = "0.0", UIMax = "5.0"))
		float timeCorrectionSpeed = .1f;
	/// <summary>The estimated owner time of non-owned objects will change instantly if it is off by this amount.</summary>
	/// <remarks>
	/// The estimated owner time will change instantly if the difference is larger than this amount (in seconds)
	/// when receiving an update. 
	/// Generally keep at default unless you have a very low send rate and expect large variance in your latencies.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float snapTimeThreshold = 1.0f;
	/// <summary>Checked when adding a received State.</summary>
	/// <remarks>Used to automatically jump to the latest received owner time when it has been this long since latest received State.</remarks>
	float receiveSnapTimeThreshold = 10.0f;
	/// <summary>How fast to lerp the position to the target SmoothState. 0 is never, 1 is instant.</summary>
	/// <remarks>
	/// Lower values mean smoother but maybe sluggish movement.
	/// Higher values mean more responsive but maybe jerky or stuttery movement.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Important, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float positionLerpSpeed = .85f;

	/// <summary>How fast to lerp the rotation to the target State. 0 is never, 1 is instant..</summary>
	/// <remarks>
	/// Lower values mean smoother but maybe sluggish movement.
	/// Higher values mean more responsive but maybe jerky or stuttery movement.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Important, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float rotationLerpSpeed = .85f;

	/// <summary>How fast to lerp the scale to the target State. 0 is never, 1 is instant.</summary>
	/// <remarks>
	/// Lower values mean smoother but maybe sluggish movement.
	/// Higher values mean more responsive but maybe jerky or stuttery movement.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Important, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float scaleLerpSpeed = .85f;

	/// <summary>Position sync mode</summary>
	/// <remarks>
	/// Fine tune how position is synced. 
	/// For objects that don't move, use SyncMode.NONE
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SyncModes)
		SyncMode syncPosition = SyncMode::XYZ;

	/// <summary>Rotation sync mode</summary>
	/// <remarks>
	/// Fine tune how rotation is synced. 
	/// For objects that don't rotate, use SyncMode.NONE
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SyncModes)
		SyncMode syncRotation = SyncMode::XYZ;

	/// <summary>Scale sync mode</summary>
	/// <remarks>
	/// Fine tune how scale is synced. 
	/// For objects that don't scale, use SyncMode.NONE
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SyncModes)
		SyncMode syncScale = SyncMode::XYZ;

	/// <summary>Velocity sync mode</summary>
	/// <remarks>
	/// Fine tune how velocity is synced.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SyncModes)
		SyncMode syncVelocity = SyncMode::XYZ;

	/// <summary>Angular velocity sync mode</summary>
	/// <remarks>
	/// Fine tune how angular velocity is synced. 
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SyncModes)
		SyncMode syncAngularVelocity = SyncMode::XYZ;

	///	<summary>Sync Movement Mode (animations)</summary>
	/// <remarks>
	/// Syncs Unreal's Movement Mode (animations) for Characters.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SyncModes)
		bool syncMovementMode = true;

	/// <summary>Compress position floats when sending over the network.</summary>
	/// <remarks>
	/// Convert position floats sent over the network to Halfs, which use half as much bandwidth but are also half as precise.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression)
		bool isPositionCompressed = false;
	/// <summary>Compress rotation floats when sending over the network.</summary>
	/// <remarks>
	/// Convert rotation floats sent over the network to Halfs, which use half as much bandwidth but are also half as precise.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression)
		bool isRotationCompressed = false;
	/// <summary>Compress scale floats when sending over the network.</summary>
	/// <remarks>
	/// Convert scale floats sent over the network to Halfs, which use half as much bandwidth but are also half as precise.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression)
		bool isScaleCompressed = false;
	/// <summary>Compress velocity floats when sending over the network.</summary>
	/// <remarks>
	/// Convert velocity floats sent over the network to Halfs, which use half as much bandwidth but are also half as precise.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression)
		bool isVelocityCompressed = false;
	/// <summary>Compress angular velocity floats when sending over the network.</summary>
	/// <remarks>
	/// Convert angular velocity floats sent over the network to Halfs, which use half as much bandwidth but are also half as precise.
	/// </remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Compression)
		bool isAngularVelocityCompressed = false;

	/// <summary>How many times per second to send network updates.</summary>
	/// <remarks>Keep in mind this can be limited by Unreal's Net Update Frequency.</remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Important)
		float sendRate = 30;

	/// <summary>Whether or not to sync origin for Origin Rebasing.</summary>
	/// <remarks>You will need this only if your levels are very large. This requires an extra byte when syncing.</remarks>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Important)
		bool isUsingOriginRebasing = false;

	/// <summary>Non-owners keep a list of recent States received over the network for interpolating.</summary>
	/// <remarks>Index 0 is the newest received State.</remarks>
	SmoothState **stateBuffer;

	/// <summary>
	/// Uses a State buffer of at least 30 for ease of use, or a buffer size in relation 
	/// to the send rate and how far back in time we want to be. Doubled buffer as estimation for forced SmoothState sends.
	/// </summary>
	int calculatedStateBufferSize = ((int)(sendRate * interpolationBackTime) + 1) * 2;

	/// <summary>The number of States in the stateBuffer</summary>
	int stateCount = 0;

	/// <summary>
	/// Used via stopLerping() to 'teleport' a synced object without unwanted lerping.
	/// Useful for player spawning and whatnot.
	/// </summary>
	bool dontLerp = false;
	/// <summary>Last time the object was teleported.</summary>
	float lastTeleportOwnerTime;

	/// <summary>Last time owner sent a SmoothState.</summary>
	float lastTimeStateWasSent;

	/// <summary>Last time a SmoothState was received on non-owner.</summary>
	float lastTimeStateWasReceived;

	/// <summary>Position owner was at when the last position SmoothState was sent.</summary>
	FVector lastPositionWhenStateWasSent;

	/// <summary>Rotation owner was at when the last rotation SmoothState was sent.</summary>
	FQuat lastRotationWhenStateWasSent = FQuat::Identity;

	/// <summary>Scale owner was at when the last scale SmoothState was sent.</summary>
	FVector lastScaleWhenStateWasSent;

	/// <summary>Velocity owner was at when the last velocity SmoothState was sent.</summary>
	FVector lastVelocityWhenStateWasSent;

	/// <summary>Angular velocity owner was at when the last angular velociy SmoothState was sent.</summary>
	FVector lastAngularVelocityWhenStateWasSent;

	/// <summary>Gets assigned to the real object to sync.</summary>
	AActor *realObjectToSync;
	/// <summary>Gets assigned to the movement component on the actor.</summary>
	UMovementComponent* movementComponent;
	/// <summary>Gets assigned to the character movement component on the actor.</summary>
	UCharacterMovementComponent* characterMovementComponent;

	/// <summary>Origin on owner when the last SmoothState was sent.</summary>
	FIntVector lastOriginWhenStateWasSent = FIntVector::ZeroValue;
	/// <summary>Latest origin received from owner</summary>
	FIntVector lastOriginWhenStateWasReceived = FIntVector::ZeroValue;

	/// <summary>Gets assigned to the real transform to sync. Use SetSceneComponentToSync() method to set it up. If
	/// this variable is not assigned, SmoothSync will sync the actor.</summary>
	UPROPERTY(BlueprintReadWrite, Category = Important)
		USceneComponent *realComponentToSync;

	/// <summary>SmoothState when extrapolation ended.</summary>
	SmoothState *extrapolationEndState;
	/// <summary>Time when extrapolation ended.</summary>
	float extrapolationStopTime;

	/// <summary>Gets set to true in order to force the state to be sent next frame on owners.</summary>
	bool forceStateSend = false;

	/// <summary>Variable we set at the beginning of Update so we only need to do the checks once a frame.</summary>
	bool sendPosition = true;
	/// <summary>Variable we set at the beginning of Update so we only need to do the checks once a frame.</summary>
	bool sendRotation = true;
	/// <summary>Variable we set at the beginning of Update so we only need to do the checks once a frame.</summary>
	bool sendScale = true;
	/// <summary>Variable we set at the beginning of Update so we only need to do the checks once a frame.</summary>
	bool sendVelocity = true;
	/// <summary>Variable we set at the beginning of Update so we only need to do the checks once a frame.</summary>
	bool sendAngularVelocity = true;
	/// <summary>Variable we set at the beginning of Update so we only need to do the checks once a frame.</summary>
	bool sendMovementMode = true;
	/// <summary>Used to turn Smooth Sync off and on.</summary>
	bool isBeingUsed = true;

	/// <summary>
	/// The last owner time received over the network
	/// </summary>
	float _ownerTime;

	/// <summary>
	/// The realTimeSinceStartup when we received the last owner time.
	/// </summary>
	float lastTimeOwnerTimeWasSet;

	/// <summary>
	/// SmoothState we fill up to better organize the data before sending it out.
	/// </summary>
	SmoothState *sendingTempState;
	/// <summary>
	/// Gets filled each frame with a SmoothState to move towards
	/// </summary>
	SmoothState *targetTempState;
	/// <summary> Used to check if low FPS causes us to skip a teleport State. </summary>
	SmoothState *latestEndStateUsed;
	/// <summary> Used to check if we should be sending a "JustStartedMoving" State. If we are teleporting, don't send one. </summary>
	FVector latestTeleportedFromPosition;
	/// <summary> Used to check if we should be sending a "JustStartedMoving" State. If we are teleporting, don't send one. </summary>
	FQuat latestTeleportedFromRotation;
	/// <summary>
	/// Reference to the Primitive Component.
	/// </summary>
	UPrimitiveComponent *primitiveComponent;
	uint8 latestSentMovementMode;
	uint8 latestReceivedMovementMode;

	/// <summary>Used to force the server to resend the latest state to all clients</summary>
	/// <remarks>
	/// This is useful when using Network Relevancy so that when an object becomes relevant on non-owners they receive
	/// a valid state immediately instead of waiting until the owner decides to send a new state. This also has the side
	/// effect of forcing the owner's origin to be re-sent which fixes an issue when combining origin rebasing and net
	/// cull distance squared.
	/// </remarks>
	bool resendLatestStateFromServer = false;

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void applyInterpolationOrExtrapolation();
	void setPosition(FVector position);
	void setRotation(const FQuat &rotation);
	void setScale(FVector scale);
	void setLinearVelocity(FVector position);
	void setAngularVelocity(FVector position);
	void interpolate(float interpolationTime, SmoothState *targetState);
	bool extrapolate(float interpolationTime, SmoothState *targetState);
	void addState(SmoothState *state);
	void addTeleportState(SmoothState *state);
	FVector getPosition();
	FQuat getRotation();
	FVector getScale();
	FVector getLinearVelocity();
	FVector getAngularVelocity();
	float GetNetworkSendInterval();
	bool shouldSendTransform();
	bool shouldSendPosition();
	bool shouldSendRotation();
	bool shouldSendScale();
	bool shouldSendVelocity();
	bool shouldSendAngularVelocity();
	bool shouldSendMovementMode();
	bool isSyncingXPosition();
	bool isSyncingYPosition();
	bool isSyncingZPosition();
	bool isSyncingXRotation();
	bool isSyncingYRotation();
	bool isSyncingZRotation();
	bool isSyncingXVelocity();
	bool isSyncingYVelocity();
	bool isSyncingZVelocity();
	bool isSyncingXScale();
	bool isSyncingYScale();
	bool isSyncingZScale();
	bool isSyncingXAngularVelocity();
	bool isSyncingYAngularVelocity();
	bool isSyncingZAngularVelocity();
	UFUNCTION(BlueprintCallable, Category = "SmoothSync")
		/// Clear the state buffer. You will call this on all unowned Actor instances on ownership changes.
		void clearBuffer();
	void stopLerping();

	UFUNCTION(BlueprintCallable, Category = "SmoothSync")
		/// Teleport the player so that position will not be interpolated on non-owners. Use teleport() on the owner and 
		/// the Actor will jump to the current owner's position on non-owners. 
		void teleport();

	UFUNCTION(BlueprintCallable, Category = "SmoothSync")
		/// Used to turn Smooth Sync on and off. True to enable Smooth Sync. False to disable Smooth Sync.
		///	Will automatically send RPCs across the network. Is meant to be called on the owned version of the Actor.
		void enableSmoothSync(bool enable);

	UFUNCTION(BlueprintCallable, Category = "SmoothSync")
		/// Forces the SmoothState (Transform) to be sent on owned objects the next time it goes through TickComponent(). 
		/// The SmoothState (Transform) will get sent next frame regardless of all limitations.
		void forceStateSendNextFrame();

	UFUNCTION(BlueprintCallable, Category = "SmoothSync")
		/// Used to set the transform that you want to sync on this SmoothSync. If this is not called, SmoothSync will sync the actor. 
		/// Must have one SmoothSync for each Transform that you want to sync. 
		void setSceneComponentToSync(USceneComponent *theComponent);

	void internalEnableSmoothSync(bool enable);
	void adjustOwnerTime();
	float getApproximateNetworkTimeOnOwner();
	float approximateNetworkTimeOnOwner = 0;
	int receivedStatesCounter;
	float updatedDeltaTime;
	bool isSimulatingPhysics;

	RestState restStatePosition = RestState::MOVING;
	RestState restStateRotation = RestState::MOVING;
	/// <summary>Counts up for each FixedUpdate() that position is the same until the atRestThresholdCount.</summary>
	float samePositionCount;
	/// <summary>Counts up for each FixedUpdate() that rotation is the same until the atRestThresholdCount.</summary>
	float sameRotationCount;
	/// <summary>Used to tell whether the object is at positional rest or not.</summary>
	bool changedPositionLastFrame;
	/// <summary>Used to tell whether the object is at rotational rest or not.</summary>
	bool changedRotationLastFrame;
	/// <summary>Is considered at rest if at same position for this many FixedUpdate()s.</summary>
	float atRestThresholdCount = .5f;
	bool triedToExtrapolateTooFar;
	bool extrapolatedLastFrame;
	float timeSpentExtrapolating;
	/// <summary>Gets set to true when position is the same for two frames in order to tell non-owners to stop extrapolating position.</summary>
	bool sendAtPositionalRestMessage = false;
	/// <summary>Gets set to true when rotation is the same for two frames in order to tell non-owners to stop extrapolating rotation.</summary>
	bool sendAtRotationalRestMessage = false;
	FVector positionLastFrame;
	FIntVector originLastFrame;
	FQuat rotationLastFrame;
	void resetFlags();
	void sendState();

	FVector latestReceivedVelocity;
	FVector latestReceivedAngularVelocity;
	bool sameVector(FVector one, FVector two, float threshold);
	/// <summary>Actor will come to positional rest if it stops moving by this amount. Used to smooth out stops and starts.</summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float atRestPositionThreshold = .05f;
	/// <summary>Actor will come to rotational rest if it stops rotating by this amount. Used to smooth out stops and starts.</summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thresholds)
		float atRestRotationThreshold = .1f;

	UFUNCTION(NetMulticast, unreliable, WithValidation)
		void ServerSendsTransformToEveryone(const TArray<uint8>&  value);
	UFUNCTION(Server, unreliable, WithValidation)
		void ClientSendsTransformToServer(const TArray<uint8>&  value);

	UFUNCTION(NetMulticast, unreliable, WithValidation)
		void SmoothSyncEnableServerToClients(bool enable);
	UFUNCTION(Server, unreliable, WithValidation)
		void SmoothSyncEnableClientToServer(bool enable);
	UFUNCTION(NetMulticast, reliable, WithValidation)
		void SmoothSyncTeleportServerToClients(FVector position, FVector rotation, FVector scale, float tempOwnerTime);
	UFUNCTION(Server, reliable, WithValidation)
		void SmoothSyncTeleportClientToServer(FVector position, FVector rotation, FVector scale, float tempOwnerTime);


	template <class T>
	void copyToBuffer(T thing);
	template <class T>
	void readFromBuffer(T* thing);

	void SerializeState(SmoothState *sendingState);
	char encodeSyncInformation(bool sendPositionFlag, bool sendRotationFlag, bool sendScaleFlag, bool sendVelocityFlag, bool sendAngularVelocityFlag, bool atPositionalRestFlag, bool atRotationalRestFlag, bool sendMovementModeFlag);
	bool shouldDeserializePosition(char syncInformation);
	bool shouldDeserializeRotation(char syncInformation);
	bool shouldDeserializeScale(char syncInformation);
	bool shouldDeserializeVelocity(char syncInformation);
	bool shouldDeserializeAngularVelocity(char syncInformation);
	bool shouldDeserializeMovementMode(char syncInformation);
	bool deserializePositionalRestFlag(char syncInformation);
	bool deserializeRotationalRestFlag(char syncInformation);

	/// <summary>Overriding this method from UActorComponent so that we can know when the object is initially replicated.</summary>
	/// <remarks>RepFlags->bNetInitial will be set whenever this Actor becomes relevant for any client.</remarks>
	bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags);

	void shouldTeleport(SmoothState *start, SmoothState *end, float interpolationTime, float *t);
	/// <summary>
	/// Hardcoded information to determine rotation syncing.
	/// </summary>
	char positionMask = 1;        // 0000_0001
	/// <summary>
	/// Hardcoded information to determine rotation syncing.
	/// </summary>
	char rotationMask = 2;        // 0000_0010
	/// <summary>
	/// Hardcoded information to determine scale syncing.
	/// </summary>
	char scaleMask = 4;			  // 0000_0100
	/// <summary>
	/// Hardcoded information to determine velocity syncing.
	/// </summary>
	char velocityMask = 8;        // 0000_1000
	/// <summary>
	/// Hardcoded information to determine angular velocity syncing.
	/// </summary>
	char angularVelocityMask = 16; // 0001_0000
	/// <summary>
	/// Hardcoded information to determine if MovementMode has changed.
	/// </summary>
	char movementModeMask = 32; // 0010_0000
	/// <summary>
	/// Hardcoded information to determine if at positional rest.
	/// </summary>
	char atPositionalRestMask = 64; // 0100_0000
	/// <summary>
	/// Hardcoded information to determine if at rotational rest.
	/// </summary>
	unsigned char atRotationalRestMask = 128; // 1000_0000
	/// <summary>
	/// Hardcoded information to determine origin rebasing
	/// </summary>
	char originRebaseMask = 1;        // 0000_0001
};