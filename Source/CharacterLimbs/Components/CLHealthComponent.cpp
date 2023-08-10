// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CLHealthComponent.h"

UCLHealthComponent::UCLHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}


void UCLHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	LimbsComponent = GetOwner()->FindComponentByClass<UCLCharacterLimbsComponent>();
	
}


void UCLHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



}

float UCLHealthComponent::TakeDamage(float Damage, AController* InstigatedBy, AActor* DamageCauser, FName BoneName)
{
	
	float damageMultipler = 1.0f;

	if (LimbsComponent.IsValid())
	{
		if (auto limbDataPtr = LimbsComponent->FindLimbDataByBone(BoneName))
		{
			damageMultipler = limbDataPtr->CharacterDamageMultiplier;
		}
	}

	const float finalDamage = Damage * damageMultipler;

	CurrentHealth = FMath::Max(CurrentHealth - finalDamage, 0.0f);

	return finalDamage;
}

