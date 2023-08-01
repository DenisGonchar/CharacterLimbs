#include "CLModularCharacter.h"
#include "CharacterLimbs/Components/CLCharacterLimbsComponent.h"

ACLModularCharacter::ACLModularCharacter()
{
	CharacterLimbsComponent = CreateDefaultSubobject<UCLCharacterLimbsComponent>("CharacterLimdsComponent");
}
