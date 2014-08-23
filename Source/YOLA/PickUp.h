

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

/**
 * 
 */

// Enum for pickup status
enum class EPickUpStatus : short
{
	EOnFloor,
	EPickedUp
};
UCLASS()
class YOLA_API APickUp : public AActor
{
	GENERATED_UCLASS_BODY()
	EPickUpStatus GetPickUpStatus();
	void SetPickUpStatus(EPickUpStatus newStatus);

private:
	EPickUpStatus PickUpStatus;
	
};
