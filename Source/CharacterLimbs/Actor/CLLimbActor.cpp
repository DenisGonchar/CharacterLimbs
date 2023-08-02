// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CLLimbActor.h"

// Sets default values
ACLLimbActor::ACLLimbActor()
{
	PrimaryActorTick.bCanEverTick = true;

	TransformComponent = CreateDefaultSubobject<USceneComponent>("TransformComponent");
	SetRootComponent(TransformComponent);

	 MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	 MeshComponent->SetupAttachment(TransformComponent);

}

// Called when the game starts or when spawned
void ACLLimbActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACLLimbActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

