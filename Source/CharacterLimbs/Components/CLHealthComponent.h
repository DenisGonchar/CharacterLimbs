#pragma once

#include "Components/ActorComponent.h"
#include "CLCharacterLimbsComponent.h"

#include "CLHealthComponent.generated.h"


UCLASS()
class UCLHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCLHealthComponent();


public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float TakeDamage(float Damage, AController* InstigatedBy, AActor* DamageCauser, FName BoneName);


public:
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() { return CurrentHealth; };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;

	
protected:
	UPROPERTY()
	float CurrentHealth;

	
	TWeakObjectPtr<UCLCharacterLimbsComponent> LimbsComponent;
};
