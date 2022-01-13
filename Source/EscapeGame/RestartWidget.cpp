// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "EscapeGamePlayerController.h"

#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void URestartWidget::NativeOnInitialized() 
{
	Super::NativeOnInitialized();

	if (RestartButton != nullptr) RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartCkick);
}

void URestartWidget::OnRestartCkick()
{

	AEscapeGamePlayerController* PlayerController = Cast<AEscapeGamePlayerController>(GetOwningPlayer());

	if (PlayerController != nullptr)
	{
		PlayerController->HideRestartWidget();
	}

	UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
}
