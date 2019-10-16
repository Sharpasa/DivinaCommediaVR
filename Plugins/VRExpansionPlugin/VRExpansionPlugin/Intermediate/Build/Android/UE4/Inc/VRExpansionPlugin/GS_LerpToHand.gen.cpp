// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VRExpansionPlugin/Public/GripScripts/GS_LerpToHand.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGS_LerpToHand() {}
// Cross Module References
	VREXPANSIONPLUGIN_API UFunction* Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_VRExpansionPlugin();
	VREXPANSIONPLUGIN_API UEnum* Z_Construct_UEnum_VRExpansionPlugin_EVRLerpInterpolationMode();
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UGS_LerpToHand_NoRegister();
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UGS_LerpToHand();
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UVRGripScriptBase();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeFloatCurve();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_VRExpansionPlugin, nullptr, "VRLerpToHandFinishedSignature__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static UEnum* EVRLerpInterpolationMode_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_VRExpansionPlugin_EVRLerpInterpolationMode, Z_Construct_UPackage__Script_VRExpansionPlugin(), TEXT("EVRLerpInterpolationMode"));
		}
		return Singleton;
	}
	template<> VREXPANSIONPLUGIN_API UEnum* StaticEnum<EVRLerpInterpolationMode>()
	{
		return EVRLerpInterpolationMode_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EVRLerpInterpolationMode(EVRLerpInterpolationMode_StaticEnum, TEXT("/Script/VRExpansionPlugin"), TEXT("EVRLerpInterpolationMode"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_VRExpansionPlugin_EVRLerpInterpolationMode_Hash() { return 73675627U; }
	UEnum* Z_Construct_UEnum_VRExpansionPlugin_EVRLerpInterpolationMode()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_VRExpansionPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EVRLerpInterpolationMode"), 0, Get_Z_Construct_UEnum_VRExpansionPlugin_EVRLerpInterpolationMode_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EVRLerpInterpolationMode::QuatInterp", (int64)EVRLerpInterpolationMode::QuatInterp },
				{ "EVRLerpInterpolationMode::EulerInterp", (int64)EVRLerpInterpolationMode::EulerInterp },
				{ "EVRLerpInterpolationMode::DualQuatInterp", (int64)EVRLerpInterpolationMode::DualQuatInterp },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Comment", "/** Different methods for interpolating rotation between transforms */" },
				{ "DualQuatInterp.Comment", "/** Dual quaternion interpolation, follows helix or screw-motion path between keyframes.   */" },
				{ "DualQuatInterp.Name", "EVRLerpInterpolationMode::DualQuatInterp" },
				{ "DualQuatInterp.ToolTip", "Dual quaternion interpolation, follows helix or screw-motion path between keyframes." },
				{ "EulerInterp.Comment", "/** Rotor or Euler Angle interpolation. */" },
				{ "EulerInterp.Name", "EVRLerpInterpolationMode::EulerInterp" },
				{ "EulerInterp.ToolTip", "Rotor or Euler Angle interpolation." },
				{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
				{ "QuatInterp.Comment", "/** Shortest Path or Quaternion interpolation for the rotation. */" },
				{ "QuatInterp.Name", "EVRLerpInterpolationMode::QuatInterp" },
				{ "QuatInterp.ToolTip", "Shortest Path or Quaternion interpolation for the rotation." },
				{ "ToolTip", "Different methods for interpolating rotation between transforms" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_VRExpansionPlugin,
				nullptr,
				"EVRLerpInterpolationMode",
				"EVRLerpInterpolationMode",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void UGS_LerpToHand::StaticRegisterNativesUGS_LerpToHand()
	{
	}
	UClass* Z_Construct_UClass_UGS_LerpToHand_NoRegister()
	{
		return UGS_LerpToHand::StaticClass();
	}
	struct Z_Construct_UClass_UGS_LerpToHand_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OptionalCurveToFollow_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_OptionalCurveToFollow;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseCurve_MetaData[];
#endif
		static void NewProp_bUseCurve_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseCurve;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnLerpToHandFinished_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnLerpToHandFinished;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LerpInterpolationMode_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_LerpInterpolationMode;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_LerpInterpolationMode_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxSpeedForLerp_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxSpeedForLerp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MinSpeedForLerp_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MinSpeedForLerp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LerpDuration_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_LerpDuration;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MinDistanceForLerp_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MinDistanceForLerp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGS_LerpToHand_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UVRGripScriptBase,
		(UObject* (*)())Z_Construct_UPackage__Script_VRExpansionPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "VRExpansionPlugin" },
		{ "Comment", "// A grip script that causes new grips to lerp to the hand (from their current position to where they are supposed to sit).\n// It turns off when the lerp is complete.\n" },
		{ "HideCategories", "DefaultSettings" },
		{ "IncludePath", "GripScripts/GS_LerpToHand.h" },
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "A grip script that causes new grips to lerp to the hand (from their current position to where they are supposed to sit).\nIt turns off when the lerp is complete." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OptionalCurveToFollow_MetaData[] = {
		{ "Category", "LerpCurve" },
		{ "Comment", "// The curve to follow when using a curve map, only uses from 0.0 - 1.0 of the curve timeline and maps it across the entire duration\n" },
		{ "editcondition", "bUseCurve" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
		{ "ToolTip", "The curve to follow when using a curve map, only uses from 0.0 - 1.0 of the curve timeline and maps it across the entire duration" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OptionalCurveToFollow = { "OptionalCurveToFollow", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGS_LerpToHand, OptionalCurveToFollow), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OptionalCurveToFollow_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OptionalCurveToFollow_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_bUseCurve_MetaData[] = {
		{ "Category", "LerpCurve" },
		{ "Comment", "// Whether to use a curve map to map the lerp to\n" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
		{ "ToolTip", "Whether to use a curve map to map the lerp to" },
	};
#endif
	void Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_bUseCurve_SetBit(void* Obj)
	{
		((UGS_LerpToHand*)Obj)->bUseCurve = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_bUseCurve = { "bUseCurve", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UGS_LerpToHand), &Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_bUseCurve_SetBit, METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_bUseCurve_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_bUseCurve_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OnLerpToHandFinished_MetaData[] = {
		{ "Category", "LerpEvents" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OnLerpToHandFinished = { "OnLerpToHandFinished", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGS_LerpToHand, OnLerpToHandFinished), Z_Construct_UDelegateFunction_VRExpansionPlugin_VRLerpToHandFinishedSignature__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OnLerpToHandFinished_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OnLerpToHandFinished_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpInterpolationMode_MetaData[] = {
		{ "Category", "LerpSettings" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpInterpolationMode = { "LerpInterpolationMode", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGS_LerpToHand, LerpInterpolationMode), Z_Construct_UEnum_VRExpansionPlugin_EVRLerpInterpolationMode, METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpInterpolationMode_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpInterpolationMode_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpInterpolationMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MaxSpeedForLerp_MetaData[] = {
		{ "Category", "LerpSettings" },
		{ "Comment", "// The maximum speed (in UU per second) that the lerp should have across the initial grip distance\n// Will slow the LerpSpeed down to try and maintain this initial speed if required\n" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
		{ "ToolTip", "The maximum speed (in UU per second) that the lerp should have across the initial grip distance\nWill slow the LerpSpeed down to try and maintain this initial speed if required" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MaxSpeedForLerp = { "MaxSpeedForLerp", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGS_LerpToHand, MaxSpeedForLerp), METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MaxSpeedForLerp_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MaxSpeedForLerp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinSpeedForLerp_MetaData[] = {
		{ "Category", "LerpSettings" },
		{ "Comment", "// The minimum speed (in UU per second) that that the lerp should have across the initial grip distance\n// Will speed the LerpSpeed up to try and maintain this initial speed if required\n" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
		{ "ToolTip", "The minimum speed (in UU per second) that that the lerp should have across the initial grip distance\nWill speed the LerpSpeed up to try and maintain this initial speed if required" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinSpeedForLerp = { "MinSpeedForLerp", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGS_LerpToHand, MinSpeedForLerp), METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinSpeedForLerp_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinSpeedForLerp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpDuration_MetaData[] = {
		{ "Category", "LerpSettings" },
		{ "Comment", "// How many seconds the lerp should take\n" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
		{ "ToolTip", "How many seconds the lerp should take" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpDuration = { "LerpDuration", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGS_LerpToHand, LerpDuration), METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpDuration_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpDuration_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinDistanceForLerp_MetaData[] = {
		{ "Category", "LerpSettings" },
		{ "Comment", "// If the initial grip distance is closer than this value then the lerping will not be performed.\n" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_LerpToHand.h" },
		{ "ToolTip", "If the initial grip distance is closer than this value then the lerping will not be performed." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinDistanceForLerp = { "MinDistanceForLerp", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGS_LerpToHand, MinDistanceForLerp), METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinDistanceForLerp_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinDistanceForLerp_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGS_LerpToHand_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OptionalCurveToFollow,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_bUseCurve,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_OnLerpToHandFinished,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpInterpolationMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpInterpolationMode_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MaxSpeedForLerp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinSpeedForLerp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_LerpDuration,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_LerpToHand_Statics::NewProp_MinDistanceForLerp,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGS_LerpToHand_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGS_LerpToHand>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGS_LerpToHand_Statics::ClassParams = {
		&UGS_LerpToHand::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGS_LerpToHand_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGS_LerpToHand_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UGS_LerpToHand_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGS_LerpToHand()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGS_LerpToHand_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGS_LerpToHand, 285911307);
	template<> VREXPANSIONPLUGIN_API UClass* StaticClass<UGS_LerpToHand>()
	{
		return UGS_LerpToHand::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGS_LerpToHand(Z_Construct_UClass_UGS_LerpToHand, &UGS_LerpToHand::StaticClass, TEXT("/Script/VRExpansionPlugin"), TEXT("UGS_LerpToHand"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGS_LerpToHand);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
