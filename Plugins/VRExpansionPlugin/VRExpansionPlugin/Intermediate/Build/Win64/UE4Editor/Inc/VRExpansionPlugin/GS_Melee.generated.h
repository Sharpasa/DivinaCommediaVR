// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef VREXPANSIONPLUGIN_GS_Melee_generated_h
#error "GS_Melee.generated.h already included, missing '#pragma once' in GS_Melee.h"
#endif
#define VREXPANSIONPLUGIN_GS_Melee_generated_h

#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_12_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Statics; \
	VREXPANSIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> VREXPANSIONPLUGIN_API UScriptStruct* StaticStruct<struct FBPMelee_SurfacePair>();

#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_29_DELEGATE \
struct _Script_VRExpansionPlugin_eventVROnMeleeIsLodged_Parms \
{ \
	bool IsWeaponLodged; \
}; \
static inline void FVROnMeleeIsLodged_DelegateWrapper(const FMulticastScriptDelegate& VROnMeleeIsLodged, bool IsWeaponLodged) \
{ \
	_Script_VRExpansionPlugin_eventVROnMeleeIsLodged_Parms Parms; \
	Parms.IsWeaponLodged=IsWeaponLodged ? true : false; \
	VROnMeleeIsLodged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_RPC_WRAPPERS
#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_RPC_WRAPPERS_NO_PURE_DECLS
#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGS_Melee(); \
	friend struct Z_Construct_UClass_UGS_Melee_Statics; \
public: \
	DECLARE_CLASS(UGS_Melee, UVRGripScriptBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VRExpansionPlugin"), NO_API) \
	DECLARE_SERIALIZER(UGS_Melee)


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_INCLASS \
private: \
	static void StaticRegisterNativesUGS_Melee(); \
	friend struct Z_Construct_UClass_UGS_Melee_Statics; \
public: \
	DECLARE_CLASS(UGS_Melee, UVRGripScriptBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VRExpansionPlugin"), NO_API) \
	DECLARE_SERIALIZER(UGS_Melee)


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGS_Melee(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGS_Melee) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGS_Melee); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGS_Melee); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGS_Melee(UGS_Melee&&); \
	NO_API UGS_Melee(const UGS_Melee&); \
public:


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGS_Melee(UGS_Melee&&); \
	NO_API UGS_Melee(const UGS_Melee&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGS_Melee); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGS_Melee); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGS_Melee)


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_PRIVATE_PROPERTY_OFFSET
#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_35_PROLOG
#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_PRIVATE_PROPERTY_OFFSET \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_RPC_WRAPPERS \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_INCLASS \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_PRIVATE_PROPERTY_OFFSET \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_RPC_WRAPPERS_NO_PURE_DECLS \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_INCLASS_NO_PURE_DECLS \
	DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h_38_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VREXPANSIONPLUGIN_API UClass* StaticClass<class UGS_Melee>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DivinaCommediaVR_Plugins_VRExpansionPlugin_VRExpansionPlugin_Source_VRExpansionPlugin_Public_GripScripts_GS_Melee_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
