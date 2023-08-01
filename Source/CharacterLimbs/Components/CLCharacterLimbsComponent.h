#pragma once

#include "Components/ActorComponent.h"

#include "CLCharacterLimbsComponent.generated.h"

class USkeletalMeshComponent;
class AController;
class UPrimitiveComponent;
class UDamageType;

USTRUCT(BlueprintType)
struct FCLLimdData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* MeshComponent;
	
	
};

UCLASS()
class UCLCharacterLimbsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCLLimdData> Limbs;

protected:
	
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage,AController* InstigatedBy, FVector HitLocation,UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser);

	
};
