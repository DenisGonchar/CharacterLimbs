#pragma once

#include "GameFramework/Character.h"

#include "CLModularCharacter.generated.h"

class UCLCharacterLimbsComponent;

UCLASS()
class ACLModularCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACLModularCharacter();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCLCharacterLimbsComponent* CharacterLimbsComponent;
	
};
