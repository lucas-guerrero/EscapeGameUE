// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyCharacter.h"

#include <TimerManager.h>
#include <DrawDebugHelpers.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "PatateProjectil.h"
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
AEnnemyCharacter::AEnnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnnemyCharacter::ThrowPatate()
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Patate !!"));
	if (PatateClass == nullptr) return;

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);

	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
	APatateProjectil* Patate = GetWorld()->SpawnActorDeferred<APatateProjectil>(PatateClass, SpawnTransform);

	Patate->GetProjectileMouvementComponent()->InitialSpeed = 2200.f;
	Patate->FinishSpawning(SpawnTransform);
}

// Called every frame
void AEnnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	
	// wheter the enemy could see the player
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			// Start throwing patate
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnnemyCharacter::ThrowPatate, ThrowingInterval, true, ThrowDelay);
		}
		else
		{
			// Stop throwing patate
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	// wheter the enemy could see the player the last frame
	bPreviousCanSeePlayer = bCanSeePlayer;
}

// Called to bind functionality to input
void AEnnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnnemyCharacter::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr) return false;

	if(CanSeeActor(TargetActor))
	{
		FVector Start = SightSource->GetComponentLocation();
		FVector End = TargetActor->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		LookAtRotation.Pitch = 0;
		LookAtRotation.Roll = 0;

		// Set the rotation
		SetActorRotation(LookAtRotation);
		return true;
	}

	return false;
}

bool AEnnemyCharacter::CanSeeActor(const AActor* TargetActor) const
{
	if (TargetActor == nullptr) return false;

	// Store the result of the line trace
	FHitResult Hit;

	// the line
	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();

	// Param
	FCollisionQueryParams QueryParam;
	QueryParam.AddIgnoredActor(this);
	QueryParam.AddIgnoredActor(TargetActor);

	// the trace channel we want to compage against
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	// Execute the line trace
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParam);

	// Show the trace line
	if(!Hit.bBlockingHit) DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}

