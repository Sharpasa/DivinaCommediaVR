// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VRExpansionPlugin/Public/GripScripts/GS_Melee.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGS_Melee() {}
// Cross Module References
	VREXPANSIONPLUGIN_API UFunction* Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_VRExpansionPlugin();
	VREXPANSIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FBPMelee_SurfacePair();
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UGS_Melee_NoRegister();
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UGS_Melee();
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UVRGripScriptBase();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics
	{
		struct _Script_VRExpansionPlugin_eventVROnMeleeIsLodged_Parms
		{
			bool IsWeaponLodged;
		};
		static void NewProp_IsWeaponLodged_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsWeaponLodged;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::NewProp_IsWeaponLodged_SetBit(void* Obj)
	{
		((_Script_VRExpansionPlugin_eventVROnMeleeIsLodged_Parms*)Obj)->IsWeaponLodged = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::NewProp_IsWeaponLodged = { "IsWeaponLodged", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(_Script_VRExpansionPlugin_eventVROnMeleeIsLodged_Parms), &Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::NewProp_IsWeaponLodged_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::NewProp_IsWeaponLodged,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Event thrown when we the melee weapon becomes lodged\n" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_Melee.h" },
		{ "ToolTip", "Event thrown when we the melee weapon becomes lodged" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_VRExpansionPlugin, nullptr, "VROnMeleeIsLodged__DelegateSignature", nullptr, nullptr, sizeof(_Script_VRExpansionPlugin_eventVROnMeleeIsLodged_Parms), Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
class UScriptStruct* FBPMelee_SurfacePair::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern VREXPANSIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBPMelee_SurfacePair, Z_Construct_UPackage__Script_VRExpansionPlugin(), TEXT("BPMelee_SurfacePair"), sizeof(FBPMelee_SurfacePair), Get_Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Hash());
	}
	return Singleton;
}
template<> VREXPANSIONPLUGIN_API UScriptStruct* StaticStruct<FBPMelee_SurfacePair>()
{
	return FBPMelee_SurfacePair::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBPMelee_SurfacePair(FBPMelee_SurfacePair::StaticStruct, TEXT("/Script/VRExpansionPlugin"), TEXT("BPMelee_SurfacePair"), false, nullptr, nullptr);
static struct FScriptStruct_VRExpansionPlugin_StaticRegisterNativesFBPMelee_SurfacePair
{
	FScriptStruct_VRExpansionPlugin_StaticRegisterNativesFBPMelee_SurfacePair()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("BPMelee_SurfacePair")),new UScriptStruct::TCppStructOps<FBPMelee_SurfacePair>);
	}
} ScriptStruct_VRExpansionPlugin_StaticRegisterNativesFBPMelee_SurfacePair;
	struct Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GripScripts/GS_Melee.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBPMelee_SurfacePair>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_VRExpansionPlugin,
		nullptr,
		&NewStructOps,
		"BPMelee_SurfacePair",
		sizeof(FBPMelee_SurfacePair),
		alignof(FBPMelee_SurfacePair),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FBPMelee_SurfacePair()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_VRExpansionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BPMelee_SurfacePair"), sizeof(FBPMelee_SurfacePair), Get_Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBPMelee_SurfacePair_Hash() { return 3742358852U; }
	void UGS_Melee::StaticRegisterNativesUGS_Melee()
	{
	}
	UClass* Z_Construct_UClass_UGS_Melee_NoRegister()
	{
		return UGS_Melee::StaticClass();
	}
	struct Z_Construct_UClass_UGS_Melee_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnMeleeLodgedChanged_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnMeleeLodgedChanged;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGS_Melee_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UVRGripScriptBase,
		(UObject* (*)())Z_Construct_UPackage__Script_VRExpansionPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_Melee_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "VRExpansionPlugin" },
		{ "Comment", "/**\n* A Melee grip script *CURRENTLY WIP, DO NOT USE!!!*\n*/" },
		{ "HideCategories", "DefaultSettings" },
		{ "IncludePath", "GripScripts/GS_Melee.h" },
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_Melee.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "A Melee grip script *CURRENTLY WIP, DO NOT USE!!!*" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_Melee_Statics::NewProp_OnMeleeLodgedChanged_MetaData[] = {
		{ "Category", "MeleeEvents" },
		{ "Comment", "// Call to use an object\n" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_Melee.h" },
		{ "ToolTip", "Call to use an object" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGS_Melee_Statics::NewProp_OnMeleeLodgedChanged = { "OnMeleeLodgedChanged", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGS_Melee, OnMeleeLodgedChanged), Z_Construct_UDelegateFunction_VRExpansionPlugin_VROnMeleeIsLodged__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UGS_Melee_Statics::NewProp_OnMeleeLodgedChanged_MetaData, ARRAY_COUNT(Z_Construct_UClass_UGS_Melee_Statics::NewProp_OnMeleeLodgedChanged_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGS_Melee_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGS_Melee_Statics::NewProp_OnMeleeLodgedChanged,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGS_Melee_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGS_Melee>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGS_Melee_Statics::ClassParams = {
		&UGS_Melee::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGS_Melee_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_UGS_Melee_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGS_Melee_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UGS_Melee_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGS_Melee()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGS_Melee_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGS_Melee, 1332280868);
	template<> VREXPANSIONPLUGIN_API UClass* StaticClass<UGS_Melee>()
	{
		return UGS_Melee::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGS_Melee(Z_Construct_UClass_UGS_Melee, &UGS_Melee::StaticClass, TEXT("/Script/VRExpansionPlugin"), TEXT("UGS_Melee"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGS_Melee);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
