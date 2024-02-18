// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CrowdPF/Public/CrowdPF.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCrowdPF() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	CROWDPF_API UScriptStruct* Z_Construct_UScriptStruct_FCrowdPFOptions();
	UPackage* Z_Construct_UPackage__Script_CrowdPF();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_CrowdPFOptions;
class UScriptStruct* FCrowdPFOptions::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_CrowdPFOptions.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_CrowdPFOptions.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCrowdPFOptions, (UObject*)Z_Construct_UPackage__Script_CrowdPF(), TEXT("CrowdPFOptions"));
	}
	return Z_Registration_Info_UScriptStruct_CrowdPFOptions.OuterSingleton;
}
template<> CROWDPF_API UScriptStruct* StaticStruct<FCrowdPFOptions>()
{
	return FCrowdPFOptions::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FCrowdPFOptions_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CellSize_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_CellSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OffsetX_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_OffsetX;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OffsetY_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_OffsetY;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Rows_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Rows;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Cols_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Cols;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlaneHeight_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_PlaneHeight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CostTraceYStart_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CostTraceYStart;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CostTraceDirection_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CostTraceDirection;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SignificantCostReduction_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_SignificantCostReduction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bDebugDraw_MetaData[];
#endif
		static void NewProp_bDebugDraw_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bDebugDraw;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bDrawCoords_MetaData[];
#endif
		static void NewProp_bDrawCoords_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawCoords;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bDrawCosts_MetaData[];
#endif
		static void NewProp_bDrawCosts_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawCosts;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bDrawIntegration_MetaData[];
#endif
		static void NewProp_bDrawIntegration_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawIntegration;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bDrawFlows_MetaData[];
#endif
		static void NewProp_bDrawFlows_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawFlows;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCrowdPFOptions>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CellSize_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CellSize = { "CellSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, CellSize), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CellSize_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CellSize_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetX_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetX = { "OffsetX", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, OffsetX), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetX_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetX_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetY_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetY = { "OffsetY", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, OffsetY), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetY_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetY_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Rows_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Rows = { "Rows", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, Rows), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Rows_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Rows_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Cols_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Cols = { "Cols", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, Cols), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Cols_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Cols_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_PlaneHeight_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_PlaneHeight = { "PlaneHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, PlaneHeight), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_PlaneHeight_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_PlaneHeight_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceYStart_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceYStart = { "CostTraceYStart", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, CostTraceYStart), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceYStart_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceYStart_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceDirection_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceDirection = { "CostTraceDirection", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, CostTraceDirection), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceDirection_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceDirection_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_SignificantCostReduction_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_SignificantCostReduction = { "SignificantCostReduction", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCrowdPFOptions, SignificantCostReduction), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_SignificantCostReduction_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_SignificantCostReduction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDebugDraw_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// 25% reduction\n" },
#endif
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "25% reduction" },
#endif
	};
#endif
	void Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDebugDraw_SetBit(void* Obj)
	{
		((FCrowdPFOptions*)Obj)->bDebugDraw = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDebugDraw = { "bDebugDraw", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FCrowdPFOptions), &Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDebugDraw_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDebugDraw_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDebugDraw_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCoords_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCoords_SetBit(void* Obj)
	{
		((FCrowdPFOptions*)Obj)->bDrawCoords = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCoords = { "bDrawCoords", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FCrowdPFOptions), &Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCoords_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCoords_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCoords_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCosts_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCosts_SetBit(void* Obj)
	{
		((FCrowdPFOptions*)Obj)->bDrawCosts = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCosts = { "bDrawCosts", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FCrowdPFOptions), &Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCosts_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCosts_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCosts_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawIntegration_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawIntegration_SetBit(void* Obj)
	{
		((FCrowdPFOptions*)Obj)->bDrawIntegration = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawIntegration = { "bDrawIntegration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FCrowdPFOptions), &Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawIntegration_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawIntegration_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawIntegration_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawFlows_MetaData[] = {
		{ "Category", "Yoreei's Crowd Pathfinder" },
		{ "ModuleRelativePath", "Public/CrowdPF.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawFlows_SetBit(void* Obj)
	{
		((FCrowdPFOptions*)Obj)->bDrawFlows = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawFlows = { "bDrawFlows", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FCrowdPFOptions), &Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawFlows_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawFlows_MetaData), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawFlows_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CellSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetX,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_OffsetY,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Rows,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_Cols,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_PlaneHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceYStart,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_CostTraceDirection,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_SignificantCostReduction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDebugDraw,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCoords,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawCosts,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawIntegration,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewProp_bDrawFlows,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CrowdPF,
		nullptr,
		&NewStructOps,
		"CrowdPFOptions",
		Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::PropPointers),
		sizeof(FCrowdPFOptions),
		alignof(FCrowdPFOptions),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FCrowdPFOptions()
	{
		if (!Z_Registration_Info_UScriptStruct_CrowdPFOptions.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_CrowdPFOptions.InnerSingleton, Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_CrowdPFOptions.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_CrowdPF_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_CrowdPF_h_Statics::ScriptStructInfo[] = {
		{ FCrowdPFOptions::StaticStruct, Z_Construct_UScriptStruct_FCrowdPFOptions_Statics::NewStructOps, TEXT("CrowdPFOptions"), &Z_Registration_Info_UScriptStruct_CrowdPFOptions, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCrowdPFOptions), 4195542166U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_CrowdPF_h_2556800308(TEXT("/Script/CrowdPF"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_CrowdPF_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DooriaCPP_Plugins_CrowdPF_Source_CrowdPF_Public_CrowdPF_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
