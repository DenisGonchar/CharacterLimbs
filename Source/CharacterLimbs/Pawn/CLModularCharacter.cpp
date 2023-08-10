#include "CLModularCharacter.h"
#include "CharacterLimbs/Components/CLCharacterLimbsComponent.h"
#include "Components/CLCombinedSkeletalMeshComponent.h"
#include "Components/CLHealthComponent.h"

ACLModularCharacter::ACLModularCharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCLCombinedSkeletalMeshComponent>(ACharacter::MeshComponentName))
{
	
	CombinedSkeletalMeshComponent = CastChecked<UCLCombinedSkeletalMeshComponent>(GetMesh());

	CharacterLimbsComponent = CreateDefaultSubobject<UCLCharacterLimbsComponent>("CharacterLimdsComponent");
	HealthComponent = CreateDefaultSubobject<UCLHealthComponent>("HealthComponent");

}

UCLCombinedSkeletalMeshComponent* ACLModularCharacter::GetCombinedSkeletalMeshComponent() const
{
	return CombinedSkeletalMeshComponent;
}

float ACLModularCharacter::InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CharacterLimbsComponent->TakeDamage(Damage, EventInstigator, DamageCauser, PointDamageEvent.HitInfo.GetComponent(), PointDamageEvent.HitInfo.BoneName);

	return HealthComponent->TakeDamage(Damage, EventInstigator, DamageCauser,PointDamageEvent.HitInfo.BoneName);
}
