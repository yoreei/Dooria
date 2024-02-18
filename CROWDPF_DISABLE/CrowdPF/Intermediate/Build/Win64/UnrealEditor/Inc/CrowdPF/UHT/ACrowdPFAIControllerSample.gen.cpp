// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CrowdPF/Public/Samples/ACrowdPFAIControllerSample.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeACrowdPFAIControllerSample() {}
// Cross Module References
	AIMODULE_API UClass* Z_Construct_UClass_AAIController();
	CROWDPF_API UClass* Z_Construct_UClass_ACrowdPFAIControllerSample();
	CROWDPF_API UClass* Z_Construct_UClass_ACrowdPFAIControllerSample_NoRegister();
	UPackage* Z_Construct_UPackage__Script_CrowdPF();
// End Cross Module References
	void ACrowdPFAIControllerSample::StaticRegisterNativesACrowdPFAIControllerSample()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACrowdPFAIControllerSample);
	UClass* Z_Construct_UClass_ACrowdPFAIControllerSample_NoRegister()
	{
		return ACrowdPFAIControllerSample::StaticClass();
	}
	struct Z_Construct_UClass_ACrowdPFAIControllerSample_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACrowdPFAIControllerSample_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAIController,
		(UObject* (*)())Z_Construct_UPackage__Script_CrowdPF,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACrowdPFAIControllerSample_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACrowdPFAIControllerSample_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * This is a sample file, meant to be copied to your game files if you plan to use the Yoreei's Flow Tile Crowd Pathfinder\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Samples/ACrowdPFAIControllerSample.h" },
		{ "ModuleRelativePath", "Public/Samples/ACrowdPFAIControllerSample.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This is a sample file, meant to be copied to your game files if you plan to use the Yoreei's Flow Tile Crowd Pathfinder" },
#endif
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACrowdPFAIControllerSample_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACrowdPFAIControllerSample>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACrowdPFAIControllerSample_Statics::ClassParams = {
		&ACrowdPFAIControllerSample::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACrowdPFAIControllerSample_Statics::Class_MetaDataParams), Z_Construct_UClass_ACrowdPFAIControllerSample_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ACrowdPFAIControllerSample()
	{
		if (!Z_Registration_Info_UClass_ACrowdPFAIControllerSample.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACrowdPFAIControllerSample.OuterSingleton, Z_Construct_UClass_ACrowdPFAIControllerSample_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACrowdPFAIControllerSample.OuterSingleton;
	}
	template<> CROWDPF_API UClass* StaticClass<ACrowdPFAIControllerSample>()
	{
		return ACrowdPFAIControllerSample::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACrowdPFAIControllerSample);
	ACrowdPFAIControllerSample::~ACrowdPFAIControllerSample() {}
	struct Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_Samples_ACrowdPFAIControllerSample_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_Samples_ACrowdPFAIControllerSample_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACrowdPFAIControllerSample, ACrowdPFAIControllerSample::StaticClass, TEXT("ACrowdPFAIControllerSample"), &Z_Registration_Info_UClass_ACrowdPFAIControllerSample, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACrowdPFAIControllerSample), 2690510845U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_Samples_ACrowdPFAIControllerSample_h_1681198029(TEXT("/Script/CrowdPF"),
		Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_Samples_ACrowdPFAIControllerSample_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_Samples_ACrowdPFAIControllerSample_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
