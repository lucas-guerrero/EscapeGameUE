// Fill out your copyright notice in the Description page of Project Settings.


#include "PatateProjectil.h"
#include "HealthComponent.h"
#include "EscapeGameCharacter.h"

#include <Components/SphereComponent.h>
#include <EscapeGame/EscapeGameCharacter.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
APatateProjectil::APatateProjectil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetCollisionProfileName(FName("Patate"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &APatateProjectil::OnHit);
	RootComponent = SphereComponent;

	ProjectileMouvement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Mouvement"));
	ProjectileMouvement->InitialSpeed = 1500.f;
}

void APatateProjectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit)
{
	AEscapeGameCharacter* Player = Cast<AEscapeGameCharacter>(OtherActor);
	if (Player != nullptr)
	{
		UHealthComponent *HealthComponent = Player->FindComponentByClass<UHealthComponent>();

		HealthComponent->LoseHealth(Attack);
		Destroy();
	}
}

// Called when the game starts or when spawned
void APatateProjectil::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(3.f);
	
}

// Called every frame
void APatateProjectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

