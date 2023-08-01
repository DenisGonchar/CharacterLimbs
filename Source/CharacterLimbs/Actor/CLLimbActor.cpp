// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CLLimbActor.h"

// Sets default values
ACLLimbActor::ACLLimbActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

