

#pragma once

#include "GameFramework/Actor.h"
#include "Creature.generated.h"

/**
 * 
 */
UCLASS()
class YOLA_API ACreature : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerLevel)
	float PowerLevelToGive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dead)
	bool bIsDead;

	void Die();
	
};
