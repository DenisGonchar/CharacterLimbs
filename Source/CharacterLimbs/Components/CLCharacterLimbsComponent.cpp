#include "CLCharacterLimbsComponent.h"
#include "Actor/CLLimbActor.h"
#include "CLCombinedSkeletalMeshComponent.h"


void UCLCharacterLimbsComponent::OnRegister()
{
	Super::OnRegister();

	CombinedSkeletalMesh = GetOwner()->FindComponentByClass<UCLCombinedSkeletalMeshComponent>();
	if (CombinedSkeletalMesh.IsValid())
	{
		for (const auto& limb : Limbs)
		{
			CombinedSkeletalMesh->SetBodyPartBoneName(limb.BodyPart, limb.BoneName);
		}
		
	}
}

void UCLCharacterLimbsComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CombinedSkeletalMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] CombinedSkeletalMesh is null"), *GetNameSafe(this));

	}

}

void UCLCharacterLimbsComponent::TakeDamage(float Damage, AController* InstigatedBy, AActor* DamageCauser, UPrimitiveComponent* FHitComponent, FName BoneName)
{
	if (auto SkeletalMeshComponent = Cast<USkeletalMeshComponent>(FHitComponent))
	{
		if (auto limb = FindLimbData(SkeletalMeshComponent, BoneName))
		{
			if (limb->Health > 0.0f)
			{
				TakeLimbDamage(*limb, Damage);
				if (limb->Health <= 0.0f && CombinedSkeletalMesh.IsValid())
				{
					CombinedSkeletalMesh->RemoveBodyParts({ limb->BodyPart });

					SpawnLimbActor(*limb, SkeletalMeshComponent->GetComponentTransform());
				}
			}
		}
	}
	
}

const FCLLimdData* UCLCharacterLimbsComponent::FindLimbDataByBone(FName BoneName) const
{
	if (CombinedSkeletalMesh.IsValid())
	{
		return const_cast<UCLCharacterLimbsComponent*>(this)->FindLimbData(CombinedSkeletalMesh.Get(), BoneName);

	}

	return nullptr;

}

void UCLCharacterLimbsComponent::TakeLimbDamage(FCLLimdData& Limb, float Damage)
{
	if (Limb.Health > 0.0f)
	{
		Limb.Health = FMath::Max(0.f, Limb.Health - Damage);

	}

}


void UCLCharacterLimbsComponent::SpawnLimbActor(const FCLLimdData& Limb,const FTransform& Transform)
{
	if (const auto bodyPartPtr = CombinedSkeletalMesh->GetBodyParts().Find(Limb.BodyPart))
	{
		if (LimbActorClass != nullptr && bodyPartPtr->Mesh != nullptr)
		{
			const auto LimbActor = GetWorld()->SpawnActorDeferred<ACLLimbActor>(LimbActorClass, Transform, GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			LimbActor->PrototyActor = GetOwner();
			LimbActor->GetMeshComponent()->SetSkeletalMesh(bodyPartPtr->Mesh);
			LimbActor->FinishSpawning(Transform);

		}
	}
	
}

FCLLimdData* UCLCharacterLimbsComponent::FindLimbData(USkeletalMeshComponent* MeshComponent, FName BoneName) 
{
	do
	{
		for (auto& limb : Limbs)
		{
			if (limb.BoneName == BoneName)
			{
				return &limb;
			}
		}
		BoneName = MeshComponent->GetParentBone(BoneName);

	} while (BoneName != NAME_None);

	return nullptr;

}
