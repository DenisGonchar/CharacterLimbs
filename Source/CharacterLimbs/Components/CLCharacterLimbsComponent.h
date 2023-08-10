#pragma once

#include "Components/ActorComponent.h"
#include <CLTypes.h>

#include "CLCharacterLimbsComponent.generated.h"

class USkeletalMeshComponent;
class AController;
class UPrimitiveComponent;
class UDamageType;
class ACLLimbActor;
class UCLCombinedSkeletalMeshComponent;


USTRUCT(BlueprintType)
struct FCLLimdData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CharacterDamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECLBodyPart	BodyPart;
	
};

UCLASS()
class UCLCharacterLimbsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	
	void TakeDamage(float Damage, AController* InstigatedBy, AActor* DamageCauser, UPrimitiveComponent* FHitComponent, FName BoneName);

	const FCLLimdData* FindLimbDataByBone(FName BoneName) const;
protected:
	
	void TakeLimbDamage(FCLLimdData& Limb, float Damage);

	void SpawnLimbActor(const FCLLimdData& Limb, const FTransform& Transform);

	FCLLimdData* FindLimbData(USkeletalMeshComponent* MeshComponent, FName BoneName);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCLLimdData> Limbs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACLLimbActor> LimbActorClass;

	TWeakObjectPtr<UCLCombinedSkeletalMeshComponent> CombinedSkeletalMesh;
};
