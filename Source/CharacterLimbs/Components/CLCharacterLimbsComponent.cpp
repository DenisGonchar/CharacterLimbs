#include "CLCharacterLimbsComponent.h"
#include "Actor/CLLimbActor.h"
#include "CLCombinedSkeletalMeshComponent.h"


void UCLCharacterLimbsComponent::BeginPlay()
{
	Super::BeginPlay();

	CombinedSkeletalMesh = GetOwner()->FindComponentByClass<UCLCombinedSkeletalMeshComponent>();
	if (CombinedSkeletalMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] CombinedSkeletalMesh is null"), *GetNameSafe(this));

	}

	
	GetOwner()->OnTakePointDamage.AddDynamic(this, &UCLCharacterLimbsComponent::OnTakeDamage);
	
	
}

void UCLCharacterLimbsComponent::OnTakeDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
	FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
	const UDamageType* DamageType, AActor* DamageCauser)
{
	if (auto SkeletalMeshComponent = Cast<USkeletalMeshComponent>(FHitComponent))
	{
		if (auto limb = FindLimbData(SkeletalMeshComponent, BoneName))
		{
			if (limb->Health >= 0.0f)
			{
				TakeLimbDamage(*limb, Damage);
				if (limb->Health <= 0.0f && CombinedSkeletalMesh.IsValid())
				{
					CombinedSkeletalMesh->RemoveBodyParts({limb->BodyPart});
					
					SpawnLimbActor(*limb, SkeletalMeshComponent->GetComponentTransform());
				}
			}
		}
	}

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
	if (auto bodyPartPtr = CombinedSkeletalMesh->GetBodyParts().Find(Limb.BodyPart))
	{
		if (LimbActorClass != nullptr && bodyPartPtr->Mesh != nullptr)
		{

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParameters.Owner = GetOwner();

			const auto LimbActor = GetWorld()->SpawnActor<ACLLimbActor>(LimbActorClass, Transform, SpawnParameters);
			LimbActor->GetMeshComponent()->SetSkeletalMesh(bodyPartPtr->Mesh);

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
