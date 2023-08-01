#include "CLCharacterLimbsComponent.h"

void UCLCharacterLimbsComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakePointDamage.AddDynamic(this, &UCLCharacterLimbsComponent::OnTakeDamage);
	
	
}

void UCLCharacterLimbsComponent::OnTakeDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
	FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
	const UDamageType* DamageType, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, FString::Printf(TEXT("Damage: %.2f, mesh: %s, bone: %s"), Damage, *GetNameSafe(FHitComponent), *BoneName.ToString()));
}
