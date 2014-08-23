

#pragma once

#include "GameFramework/Actor.h"
#include "PaperSpriteActor.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "Paper2DModule.h"
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
class YOLA_API APickUp : public APaperCharacter
{
	GENERATED_UCLASS_BODY()
	EPickUpStatus GetPickUpStatus();
	void SetPickUpStatus(EPickUpStatus newStatus);

	// Override Tick
	virtual void Tick(float DeltaSeconds) OVERRIDE;

	// saves my character
	//AMyAnt* MyCharacter;

	// Begin Play function
	virtual void BeginPlay() OVERRIDE;

	// The animation to play while idle 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* PickedUpAnimation;

	// The animation to play while idle 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* NormAnimation;

	//UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	//TSubobjectPtr<UPaperFlipbookComponent> Sprite;

	void PickUp();
	void Drop();
private:
	EPickUpStatus PickUpStatus;
	
};
