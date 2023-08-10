#pragma once

#include "GameFramework/Character.h"

#include "CLModularCharacter.generated.h"

class UCLCharacterLimbsComponent;
class UCLCombinedSkeletalMeshComponent;
class UCLHealthComponent;

UCLASS()
class ACLModularCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACLModularCharacter(const FObjectInitializer& ObjectInitializer);

	UCLCombinedSkeletalMeshComponent* GetCombinedSkeletalMeshComponent() const;

	virtual float InternalTakePointDamage(float Damage, struct FPointDamageEvent const& PointDamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCLCharacterLimbsComponent* CharacterLimbsComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCLCombinedSkeletalMeshComponent* CombinedSkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCLHealthComponent* HealthComponent;

};
