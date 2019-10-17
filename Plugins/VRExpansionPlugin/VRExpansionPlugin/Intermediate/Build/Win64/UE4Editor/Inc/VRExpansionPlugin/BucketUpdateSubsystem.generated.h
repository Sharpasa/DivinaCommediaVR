// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
#ifdef VREXPANSIONPLUGIN_BucketUpdateSubsystem_generated_h
#error "BucketUpdateSubsystem.generated.h already included, missing '#pragma once' in BucketUpdateSubsystem.h"
#endif
#define VREXPANSIONPLUGIN_BucketUpdateSubsystem_generated_h

#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_71_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FUpdateBucketContainer_Statics; \
	static class UScriptStruct* StaticStruct();


template<> VREXPANSIONPLUGIN_API UScriptStruct* StaticStruct<struct FUpdateBucketContainer>();

#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_48_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FUpdateBucket_Statics; \
	static class UScriptStruct* StaticStruct();


template<> VREXPANSIONPLUGIN_API UScriptStruct* StaticStruct<struct FUpdateBucket>();

#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_28_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FUpdateBucketDrop_Statics; \
	static class UScriptStruct* StaticStruct();


template<> VREXPANSIONPLUGIN_API UScriptStruct* StaticStruct<struct FUpdateBucketDrop>();

#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_23_DELEGATE \
static inline void FDynamicBucketUpdateTickSignature_DelegateWrapper(const FScriptDelegate& DynamicBucketUpdateTickSignature) \
{ \
	DynamicBucketUpdateTickSignature.ProcessDelegate<UObject>(NULL); \
}


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execIsActive) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsActive(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsObjectFunctionInBucket) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_InObject); \
		P_GET_PROPERTY(UNameProperty,Z_Param_FunctionName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsObjectFunctionInBucket(Z_Param_InObject,Z_Param_FunctionName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveObjectFromAllBuckets) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_InObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->RemoveObjectFromAllBuckets(Z_Param_InObject); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveObjectFromBucketByEvent) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_Delegate); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->RemoveObjectFromBucketByEvent(FDynamicBucketUpdateTickSignature(Z_Param_Delegate)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveObjectFromBucketByFunctionName) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_InObject); \
		P_GET_PROPERTY(UNameProperty,Z_Param_FunctionName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->RemoveObjectFromBucketByFunctionName(Z_Param_InObject,Z_Param_FunctionName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execK2_AddObjectEventToBucket) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_Delegate); \
		P_GET_PROPERTY(UIntProperty,Z_Param_UpdateHTZ); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->K2_AddObjectEventToBucket(FDynamicBucketUpdateTickSignature(Z_Param_Delegate),Z_Param_UpdateHTZ); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execK2_AddObjectToBucket) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_UpdateHTZ); \
		P_GET_OBJECT(UObject,Z_Param_InObject); \
		P_GET_PROPERTY(UNameProperty,Z_Param_FunctionName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->K2_AddObjectToBucket(Z_Param_UpdateHTZ,Z_Param_InObject,Z_Param_FunctionName); \
		P_NATIVE_END; \
	}


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execIsActive) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsActive(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsObjectFunctionInBucket) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_InObject); \
		P_GET_PROPERTY(UNameProperty,Z_Param_FunctionName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsObjectFunctionInBucket(Z_Param_InObject,Z_Param_FunctionName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveObjectFromAllBuckets) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_InObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->RemoveObjectFromAllBuckets(Z_Param_InObject); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveObjectFromBucketByEvent) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_Delegate); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->RemoveObjectFromBucketByEvent(FDynamicBucketUpdateTickSignature(Z_Param_Delegate)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveObjectFromBucketByFunctionName) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_InObject); \
		P_GET_PROPERTY(UNameProperty,Z_Param_FunctionName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->RemoveObjectFromBucketByFunctionName(Z_Param_InObject,Z_Param_FunctionName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execK2_AddObjectEventToBucket) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_Delegate); \
		P_GET_PROPERTY(UIntProperty,Z_Param_UpdateHTZ); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->K2_AddObjectEventToBucket(FDynamicBucketUpdateTickSignature(Z_Param_Delegate),Z_Param_UpdateHTZ); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execK2_AddObjectToBucket) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_UpdateHTZ); \
		P_GET_OBJECT(UObject,Z_Param_InObject); \
		P_GET_PROPERTY(UNameProperty,Z_Param_FunctionName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->K2_AddObjectToBucket(Z_Param_UpdateHTZ,Z_Param_InObject,Z_Param_FunctionName); \
		P_NATIVE_END; \
	}


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBucketUpdateSubsystem(); \
	friend struct Z_Construct_UClass_UBucketUpdateSubsystem_Statics; \
public: \
	DECLARE_CLASS(UBucketUpdateSubsystem, UEngineSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VRExpansionPlugin"), NO_API) \
	DECLARE_SERIALIZER(UBucketUpdateSubsystem)


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_INCLASS \
private: \
	static void StaticRegisterNativesUBucketUpdateSubsystem(); \
	friend struct Z_Construct_UClass_UBucketUpdateSubsystem_Statics; \
public: \
	DECLARE_CLASS(UBucketUpdateSubsystem, UEngineSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VRExpansionPlugin"), NO_API) \
	DECLARE_SERIALIZER(UBucketUpdateSubsystem)


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBucketUpdateSubsystem(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBucketUpdateSubsystem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBucketUpdateSubsystem); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBucketUpdateSubsystem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBucketUpdateSubsystem(UBucketUpdateSubsystem&&); \
	NO_API UBucketUpdateSubsystem(const UBucketUpdateSubsystem&); \
public:


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBucketUpdateSubsystem(UBucketUpdateSubsystem&&); \
	NO_API UBucketUpdateSubsystem(const UBucketUpdateSubsystem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBucketUpdateSubsystem); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBucketUpdateSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UBucketUpdateSubsystem)


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_PRIVATE_PROPERTY_OFFSET
#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_105_PROLOG
#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_PRIVATE_PROPERTY_OFFSET \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_RPC_WRAPPERS \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_INCLASS \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_PRIVATE_PROPERTY_OFFSET \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_RPC_WRAPPERS_NO_PURE_DECLS \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_INCLASS_NO_PURE_DECLS \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h_108_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VREXPANSIONPLUGIN_API UClass* StaticClass<class UBucketUpdateSubsystem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_Misc_BucketUpdateSubsystem_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
