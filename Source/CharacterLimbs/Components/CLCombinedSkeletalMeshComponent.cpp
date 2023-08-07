#include "CLCombinedSkeletalMeshComponent.h"

#include "SkeletalMeshMerge.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/Skeleton.h"
#include "CLTypes.h"



static void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMapping>& OutSectionMappings)
{
	if (InSectionMappings.Num() > 0)
	{
		OutSectionMappings.AddUninitialized(InSectionMappings.Num());
		for (int32 i = 0; i < InSectionMappings.Num(); ++i)
		{
			OutSectionMappings[i].SectionIDs = InSectionMappings[i].SectionIDs;
		}
	}
};
static void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMapping>& InUVTransformsPerMesh, TArray<FSkelMeshMergeUVTransforms>& OutUVTransformsPerMesh)
{
	if (InUVTransformsPerMesh.Num() > 0)
	{
		OutUVTransformsPerMesh.Empty();
		OutUVTransformsPerMesh.AddUninitialized(InUVTransformsPerMesh.Num());
		for (int32 i = 0; i < InUVTransformsPerMesh.Num(); ++i)
		{
			TArray<TArray<FTransform>>& OutUVTransforms = OutUVTransformsPerMesh[i].UVTransformsPerMesh;
			const TArray<FSkelMeshMergeUVTransform>& InUVTransforms = InUVTransformsPerMesh[i].UVTransformsPerMesh;
			if (InUVTransforms.Num() > 0)
			{
				OutUVTransforms.Empty();
				OutUVTransforms.AddUninitialized(InUVTransforms.Num());
				for (int32 j = 0; j < InUVTransforms.Num(); j++)
				{
					OutUVTransforms[i] = InUVTransforms[i].UVTransforms;
				}
			}
		}
	}
};
USkeletalMesh* UMeshMergeFunctionLibrary::MergeMeshes(const FSkeletalMeshMergeParams& Params)
{
	TArray<USkeletalMesh*> MeshesToMergeCopy = Params.MeshesToMerge;
	MeshesToMergeCopy.RemoveAll([](USkeletalMesh* InMesh)
		{
			return InMesh == nullptr;
		});
	if (MeshesToMergeCopy.Num() <= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Must provide multiple valid Skeletal Meshes in order to perform a merge."));
		return nullptr;
	}
	EMeshBufferAccess BufferAccess = Params.bNeedsCpuAccess ?
		EMeshBufferAccess::ForceCPUAndGPU :
		EMeshBufferAccess::Default;
	TArray<FSkelMeshMergeSectionMapping> SectionMappings;
	TArray<FSkelMeshMergeUVTransforms> UvTransforms;
	ToMergeParams(Params.MeshSectionMappings, SectionMappings);
	ToMergeParams(Params.UVTransformsPerMesh, UvTransforms);

	USkeletalMesh* BaseMesh = NewObject<USkeletalMesh>();
	if (Params.Skeleton && Params.bSkeletonBefore)
	{
		BaseMesh->SetSkeleton(Params.Skeleton);

	}

	FSkeletalMeshMerge Merger(BaseMesh, MeshesToMergeCopy, SectionMappings, Params.StripTopLODS, BufferAccess, UvTransforms.GetData());
	if (!Merger.DoMerge())
	{
		UE_LOG(LogTemp, Warning, TEXT("Merge failed!"));
		return nullptr;
	}
	if (Params.Skeleton && !Params.bSkeletonBefore)
	{
		BaseMesh->SetSkeleton(Params.Skeleton);
	}

	return BaseMesh;
}

void UCLCombinedSkeletalMeshComponent::OnRegister()
{
	Super::OnRegister();

	for (const auto& bodyPart : BodyParts)
	{
		if (bodyPart.Value.Mesh != nullptr)
		{
			CurrentBodyParts.Add(bodyPart.Key);
		}
		
	}

	TArray<FCLMeshBodyPart> meshBodyParts;
	BodyParts.GenerateValueArray(meshBodyParts);

	GenerateMesh(meshBodyParts);

}

void UCLCombinedSkeletalMeshComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCLCombinedSkeletalMeshComponent::RemoveBodyParts(const TArray<ECLBodyPart>& PartsToRemove)
{
	if (PartsToRemove.Num() != 0)
	{
		TArray<FCLMeshBodyPart> meshParts;

		for (const auto& bodyPart : CurrentBodyParts)
		{
			if (!PartsToRemove.Contains(bodyPart))
			{
				meshParts.Add(BodyParts.FindChecked(bodyPart));

			}
		}

		if (meshParts.Num() != CurrentBodyParts.Num())
		{
			GenerateMesh(meshParts);
		}

	}

	

}

const TMap<ECLBodyPart, FCLMeshBodyPart>& UCLCombinedSkeletalMeshComponent::GetBodyParts() const
{
	return BodyParts;
}

void UCLCombinedSkeletalMeshComponent::GenerateMesh(const TArray<FCLMeshBodyPart>& MeshParts)
{
	FSkeletalMeshMergeParams SkeletalMeshMergeParams;
	SkeletalMeshMergeParams.Skeleton = Skeleton;
	SkeletalMeshMergeParams.bSkeletonBefore = true;
	SkeletalMeshMergeParams.bNeedsCpuAccess = true;

	for (const auto bodyPart : MeshParts)
	{
		if (bodyPart.Mesh != nullptr)
		{
			SkeletalMeshMergeParams.MeshesToMerge.Add(bodyPart.Mesh);
		}
	}
	
	if (const auto skeletalMesh = UMeshMergeFunctionLibrary::MergeMeshes(SkeletalMeshMergeParams))
	{
		SetSkeletalMesh(skeletalMesh);
	}


}

