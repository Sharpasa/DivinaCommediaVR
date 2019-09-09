// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class USmoothSync;

class SMOOTHSYNCPLUGIN_API SmoothState
{
public:
	/// <summary>
	/// The network timestamp of the owner when the state was sent.
	/// </summary>
	float ownerTimestamp;
	/// <summary>
	/// The position of the owned object when the state was sent.
	/// </summary>
	FVector position;
	/// <summary>
	/// The rotation of the owned object when the state was sent.
	/// </summary>
	FQuat rotation;
	/// <summary>
	/// The scale of the owned object when the state was sent.
	/// </summary>
	FVector scale;
	/// <summary>
	/// The velocity of the owned object when the state was sent.
	/// </summary>
	FVector velocity;
	/// <summary>
	/// The angularVelocity of the owned object when the state was sent.
	/// </summary>
	FVector angularVelocity;

	uint8 movementMode;

	bool teleport;
	bool atPositionalRest;
	bool atRotationalRest;

	SmoothState();
	~SmoothState();
	SmoothState(SmoothState &state);
	SmoothState(SmoothState *state);
	SmoothState(USmoothSync &smoothSyncScript);
	SmoothState(USmoothSync *smoothSyncScript);
	void Lerp(SmoothState *targetState, SmoothState *start, SmoothState *end, float t);

	void defaultTheVariables();
	void copyFromSmoothSync(USmoothSync *smoothSyncScript);
	void copyFromState(SmoothState *state);
};