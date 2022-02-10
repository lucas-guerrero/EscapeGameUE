// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyCharacter.h"
#include "EscapeFunction.h"
#include "LookAtActorComponent.h"
#include "PatateProjectil.h"

#include <TimerManager.h>
#include <DrawDebugHelpers.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
AEnnemyCharacter::AEnnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Sight Source"));
	LookAtActorComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTarget(PlayerCharacter);
}

void AEnnemyCharacter::ThrowPatateAnim()
{
	if (ThrowMontage)
	{
		bool bIsMontagePlayed = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if (!bIsMontagePlayed)
		{
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 2.0f);
		}
	}
}

void AEnnemyCharacter::ThrowPatate()
{
	
	if (PatateClass == nullptr) return;

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;

	FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("RightHandSocket"));
	
	FTransform SpawnTransform(GetActorForwardVector().Rotation(), SpawnLocation);
	APatateProjectil* Patate = GetWorld()->SpawnActorDeferred<APatateProjectil>(PatateClass, SpawnTransform);

	Patate->GetProjectileMouvementComponent()->InitialSpeed = 2200.f;
	Patate->FinishSpawning(SpawnTransform);
	
}

// Called every frame
void AEnnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// wheter the enemy could see the player
	bCanSeePlayer = LookAtActorComponent->CanSeeActor();
	
	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			
			// Start throwing patate
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnnemyCharacter::ThrowPatateAnim, ThrowingInterval, true, ThrowDelay);
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

