// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VRExpansionPlugin/Public/GripScripts/GS_Slider.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGS_Slider() {}
// Cross Module References
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UGS_Slider_NoRegister();
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UGS_Slider();
	VREXPANSIONPLUGIN_API UClass* Z_Construct_UClass_UVRGripScriptBase();
	UPackage* Z_Construct_UPackage__Script_VRExpansionPlugin();
// End Cross Module References
	void UGS_Slider::StaticRegisterNativesUGS_Slider()
	{
	}
	UClass* Z_Construct_UClass_UGS_Slider_NoRegister()
	{
		return UGS_Slider::StaticClass();
	}
	struct Z_Construct_UClass_UGS_Slider_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGS_Slider_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UVRGripScriptBase,
		(UObject* (*)())Z_Construct_UPackage__Script_VRExpansionPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGS_Slider_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "VRExpansionPlugin" },
		{ "Comment", "// A Grip script that overrides the default grip behavior and adds custom clamping logic instead,\n" },
		{ "HideCategories", "DefaultSettings" },
		{ "IncludePath", "GripScripts/GS_Slider.h" },
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Public/GripScripts/GS_Slider.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "A Grip script that overrides the default grip behavior and adds custom clamping logic instead," },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGS_Slider_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGS_Slider>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGS_Slider_Statics::ClassParams = {
		&UGS_Slider::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x003010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGS_Slider_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UGS_Slider_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGS_Slider()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGS_Slider_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGS_Slider, 3039837583);
	template<> VREXPANSIONPLUGIN_API UClass* StaticClass<UGS_Slider>()
	{
		return UGS_Slider::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGS_Slider(Z_Construct_UClass_UGS_Slider, &UGS_Slider::StaticClass, TEXT("/Script/VRExpansionPlugin"), TEXT("UGS_Slider"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGS_Slider);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
