#include "CLModularCharacter.h"
#include "CharacterLimbs/Components/CLCharacterLimbsComponent.h"
#include "Components/CLCombinedSkeletalMeshComponent.h"

ACLModularCharacter::ACLModularCharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCLCombinedSkeletalMeshComponent>(ACharacter::MeshComponentName))
{
	
	CharacterLimbsComponent = CreateDefaultSubobject<UCLCharacterLimbsComponent>("CharacterLimdsComponent");
	
	CombinedSkeletalMeshComponent = CastChecked<UCLCombinedSkeletalMeshComponent>(GetMesh());

}

UCLCombinedSkeletalMeshComponent* ACLModularCharacter::GetCombinedSkeletalMeshComponent() const
{
	return CombinedSkeletalMeshComponent;
}
