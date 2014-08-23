

#include "YOLA.h"
#include "MyAnt.h"
#include "PickUp.h"


APickUp::APickUp(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	PickUpStatus = EPickUpStatus::EOnFloor;
}

EPickUpStatus APickUp::GetPickUpStatus()
{
	return PickUpStatus;
}

void APickUp::SetPickUpStatus(EPickUpStatus newStatus)
{
	PickUpStatus = newStatus;
}

void APickUp::Tick(float DeltaSeconds)
{
	if (PickUpStatus == EPickUpStatus::EPickedUp)
	{
		SetActorLocation(Cast<AMyAnt>(UGameplayStatics::GetPlayerCharacter(this, 0))->GetActorLocation() + FVector(0, 0, 150));
	}
}

void APickUp::BeginPlay()
{
	//MyCharacter = ;
}

bool APickUp::PickUp()
{
	if (Cast<AMyAnt>(UGameplayStatics::GetPlayerCharacter(this, 0))->PowerLevel >= PowerLevelRequired)
	{
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PickUpStatus = EPickUpStatus::EPickedUp;
		return true;
	}
	return false;
}

void APickUp::Drop()
{
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickUpStatus = EPickUpStatus::EOnFloor;
	SetActorLocation(UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation() + FVector(150, 0, 0));
}