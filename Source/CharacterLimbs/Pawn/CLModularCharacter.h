#pragma once

#include "GameFramework/Character.h"

#include "CLModularCharacter.generated.h"

class UCLCharacterLimbsComponent;
class UCLCombinedSkeletalMeshComponent;

UCLASS()
class ACLModularCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACLModularCharacter(const FObjectInitializer& ObjectInitializer);

	UCLCombinedSkeletalMeshComponent* GetCombinedSkeletalMeshComponent() const;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCLCharacterLimbsComponent* CharacterLimbsComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCLCombinedSkeletalMeshComponent* CombinedSkeletalMeshComponent;

};
