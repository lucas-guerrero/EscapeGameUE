// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LifeUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API ULifeUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* LifeBar;

	void UpdateLifePercent(float Value);
};
