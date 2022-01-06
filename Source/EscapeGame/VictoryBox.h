// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VictoryBox.generated.h"

UCLASS()
class ESCAPEGAME_API AVictoryBox : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = VictoryBox, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = VictoryBox, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;
	
public:	
	// Sets default values for this actor's properties
	AVictoryBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
