

#include "YOLA.h"
#include "Creature.h"


ACreature::ACreature(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bIsDead = false;
}

void ACreature::Die()
{
	Destroy();
}

