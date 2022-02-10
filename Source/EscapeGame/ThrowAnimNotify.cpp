// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowAnimNotify.h"
#include "EnnemyCharacter.h"

void UThrowAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animator)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Explosion"));
	AEnnemyCharacter* Ennemy = Cast<AEnnemyCharacter>(MeshComp->GetOwner());
	if (Ennemy)
	{
		Ennemy->ThrowPatate();
	}
}