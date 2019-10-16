// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VRExpansionPlugin/Public/Grippables/GrippablePhysicsReplication.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGrippablePhysicsReplication() {}
// Cross Module References
	VREXPANSIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FVRClientAuthReplicationData();
	UPackage* Z_Construct_UPackage__Script_VRExpansionPlugin();
	VREXPANSIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FRepMovementVR();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRepMovement();
// End Cross Module References
class UScriptStruct* FVRClientAuthReplicationData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern VREXPANSIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FVRClientAuthReplicationData, Z_Construct_UPackage__Script_VRExpansionPlugin(), TEXT("VRClientAuthReplicationData"), sizeof(FVRClientAuthReplicationData), Get_Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Hash());
	}
	return Singleton;
}
template<> VREXPANSIONPLUGIN_API UScriptStruct* StaticStruct<FVRClientAuthReplicationData>()
{
	return FVRClientAuthReplicationData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FVRClientAuthReplicationData(FVRClientAuthReplicationData::StaticStruct, TEXT("/Script/VRExpansionPlugin"), TEXT("VRClientAuthReplicationData"), false, nullptr, nullptr);
static struct FScriptStruct_VRExpansionPlugin_StaticRegisterNativesFVRClientAuthReplicationData
{
	FScriptStruct_VRExpansionPlugin_StaticRegisterNativesFVRClientAuthReplicationData()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("VRClientAuthReplicationData")),new UScriptStruct::TCppStructOps<FVRClientAuthReplicationData>);
	}
} ScriptStruct_VRExpansionPlugin_StaticRegisterNativesFVRClientAuthReplicationData;
	struct Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UpdateRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_UpdateRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseClientAuthThrowing_MetaData[];
#endif
		static void NewProp_bUseClientAuthThrowing_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseClientAuthThrowing;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Grippables/GrippablePhysicsReplication.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVRClientAuthReplicationData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_UpdateRate_MetaData[] = {
		{ "Category", "VRReplication" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "Comment", "// Rate that we will be sending throwing events to the server, not replicated, only serialized\n" },
		{ "ModuleRelativePath", "Public/Grippables/GrippablePhysicsReplication.h" },
		{ "ToolTip", "Rate that we will be sending throwing events to the server, not replicated, only serialized" },
		{ "UIMax", "100" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_UpdateRate = { "UpdateRate", nullptr, (EPropertyFlags)0x0010000080000015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FVRClientAuthReplicationData, UpdateRate), METADATA_PARAMS(Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_UpdateRate_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_UpdateRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_bUseClientAuthThrowing_MetaData[] = {
		{ "Category", "VRReplication" },
		{ "Comment", "// If True and we are using a client auth grip type then we will replicate our throws on release\n" },
		{ "ModuleRelativePath", "Public/Grippables/GrippablePhysicsReplication.h" },
		{ "ToolTip", "If True and we are using a client auth grip type then we will replicate our throws on release" },
	};
#endif
	void Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_bUseClientAuthThrowing_SetBit(void* Obj)
	{
		((FVRClientAuthReplicationData*)Obj)->bUseClientAuthThrowing = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_bUseClientAuthThrowing = { "bUseClientAuthThrowing", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FVRClientAuthReplicationData), &Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_bUseClientAuthThrowing_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_bUseClientAuthThrowing_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_bUseClientAuthThrowing_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_UpdateRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::NewProp_bUseClientAuthThrowing,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_VRExpansionPlugin,
		nullptr,
		&NewStructOps,
		"VRClientAuthReplicationData",
		sizeof(FVRClientAuthReplicationData),
		alignof(FVRClientAuthReplicationData),
		Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FVRClientAuthReplicationData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_VRExpansionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("VRClientAuthReplicationData"), sizeof(FVRClientAuthReplicationData), Get_Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FVRClientAuthReplicationData_Hash() { return 1647610208U; }
class UScriptStruct* FRepMovementVR::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern VREXPANSIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FRepMovementVR_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FRepMovementVR, Z_Construct_UPackage__Script_VRExpansionPlugin(), TEXT("RepMovementVR"), sizeof(FRepMovementVR), Get_Z_Construct_UScriptStruct_FRepMovementVR_Hash());
	}
	return Singleton;
}
template<> VREXPANSIONPLUGIN_API UScriptStruct* StaticStruct<FRepMovementVR>()
{
	return FRepMovementVR::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FRepMovementVR(FRepMovementVR::StaticStruct, TEXT("/Script/VRExpansionPlugin"), TEXT("RepMovementVR"), false, nullptr, nullptr);
static struct FScriptStruct_VRExpansionPlugin_StaticRegisterNativesFRepMovementVR
{
	FScriptStruct_VRExpansionPlugin_StaticRegisterNativesFRepMovementVR()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("RepMovementVR")),new UScriptStruct::TCppStructOps<FRepMovementVR>);
	}
} ScriptStruct_VRExpansionPlugin_StaticRegisterNativesFRepMovementVR;
	struct Z_Construct_UScriptStruct_FRepMovementVR_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRepMovementVR_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/*static TAutoConsoleVariable<int32> CVarEnableCustomVRPhysicsReplication(\n\x09TEXT(\"vr.VRExpansion.EnableCustomVRPhysicsReplication\"),\n\x09""0,\n\x09TEXT(\"Enable valves input controller that overrides legacy input.\\n\")\n\x09TEXT(\" 0: use the engines default input mapping (default), will also be default if vr.SteamVR.EnableVRInput is enabled\\n\")\n\x09TEXT(\" 1: use the valve input controller. You will have to define input bindings for the controllers you want to support.\"),\n\x09""ECVF_ReadOnly);*/" },
		{ "ModuleRelativePath", "Public/Grippables/GrippablePhysicsReplication.h" },
		{ "ToolTip", "static TAutoConsoleVariable<int32> CVarEnableCustomVRPhysicsReplication(\n       TEXT(\"vr.VRExpansion.EnableCustomVRPhysicsReplication\"),\n       0,\n       TEXT(\"Enable valves input controller that overrides legacy input.\\n\")\n       TEXT(\" 0: use the engines default input mapping (default), will also be default if vr.SteamVR.EnableVRInput is enabled\\n\")\n       TEXT(\" 1: use the valve input controller. You will have to define input bindings for the controllers you want to support.\"),\n       ECVF_ReadOnly);" },
	};
#endif
	void* Z_Construct_UScriptStruct_FRepMovementVR_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRepMovementVR>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRepMovementVR_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_VRExpansionPlugin,
		Z_Construct_UScriptStruct_FRepMovement,
		&NewStructOps,
		"RepMovementVR",
		sizeof(FRepMovementVR),
		alignof(FRepMovementVR),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FRepMovementVR_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FRepMovementVR_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FRepMovementVR()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FRepMovementVR_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_VRExpansionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("RepMovementVR"), sizeof(FRepMovementVR), Get_Z_Construct_UScriptStruct_FRepMovementVR_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FRepMovementVR_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FRepMovementVR_Hash() { return 3634184880U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
