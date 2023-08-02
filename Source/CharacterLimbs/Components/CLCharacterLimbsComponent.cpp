#include "CLCharacterLimbsComponent.h"
#include "Actor/CLLimbActor.h"

void UCLCharacterLimbsComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakePointDamage.AddDynamic(this, &UCLCharacterLimbsComponent::OnTakeDamage);
	
	
}

void UCLCharacterLimbsComponent::OnTakeDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
	FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
	const UDamageType* DamageType, AActor* DamageCauser)
{
	if (auto SkeletalMeshComponent = Cast<USkeletalMeshComponent>(FHitComponent))
	{
		do
		{
			for (auto& limb : Limbs)
			{
				if (limb.BoneName == BoneName)
				{
					if (!FMath::IsNearlyZero(limb.Health))
					{
						TakeLimbDamage(limb, Damage);
					
						if (FMath::IsNearlyZero(limb.Health))
						{
							SpawnLimbActor(limb, SkeletalMeshComponent->GetComponentTransform());

						}
						
					}

					break;
					
				}
			}
			BoneName = SkeletalMeshComponent->GetParentBone(BoneName);

		} 
		while (BoneName != NAME_None);

	}
	
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, FString::Printf(TEXT("Damage: %.2f, mesh: %s, bone: %s"), Damage, *GetNameSafe(FHitComponent), *BoneName.ToString()));
}

void UCLCharacterLimbsComponent::TakeLimbDamage(FCLLimdData& Limb, float Damage)
{
	if (Limb.Health > 0.0f)
	{
		Limb.Health = FMath::Max(0.f, Limb.Health - Damage);

		if (FMath::IsNearlyZero(Limb.Health))
		{
			if (Limb.MeshComponent != nullptr)
			{
				Limb.MeshComponent->SetVisibility(false, true);
				Limb.MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
	}
	

}


void UCLCharacterLimbsComponent::SpawnLimbActor(const FCLLimdData& Limb,const FTransform& Transform)
{
	if (LimbActorClass != nullptr && Limb.MeshComponent != nullptr && Limb.MeshComponent->SkeletalMesh != nullptr)
	{

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Owner = GetOwner();
		
		const auto LimbActor = GetWorld()->SpawnActor<ACLLimbActor>(LimbActorClass, Transform, SpawnParameters);
		LimbActor->GetMeshComponent()->SetSkeletalMesh(Limb.MeshComponent->SkeletalMesh);

	}
}
