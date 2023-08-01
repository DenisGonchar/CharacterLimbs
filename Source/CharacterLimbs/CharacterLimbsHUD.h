// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CharacterLimbsHUD.generated.h"

UCLASS()
class ACharacterLimbsHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACharacterLimbsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

