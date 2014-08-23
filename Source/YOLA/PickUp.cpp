

#include "YOLA.h"
#include "PickUp.h"


APickUp::APickUp(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

EPickUpStatus APickUp::GetPickUpStatus()
{
	return PickUpStatus;
}

void APickUp::SetPickUpStatus(EPickUpStatus newStatus)
{
	PickUpStatus = newStatus;
}
