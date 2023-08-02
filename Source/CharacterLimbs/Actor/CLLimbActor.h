// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLLimbActor.generated.h"

class USceneComponent;
class USkeletalMeshComponent;

UCLASS()
class CHARACTERLIMBS_API ACLLimbActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLLimbActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* TransformComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* MeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
