

#pragma once

#include "PaperCharacter.h"
#include "GameFramework/Character.h"
#include "PickUp.h"
#include "PaperFlipbook.h"
#include "Paper2DModule.h"
#include "Creature.h"
#include "MyAnt.generated.h"

/**
 * 
 */
UCLASS()
class YOLA_API AMyAnt : public APaperCharacter
{
	GENERATED_UCLASS_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void PickUp();

	// bool if player is picking up something , update animation and dont carry 2 things
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = lifts)
	bool bBroLifts;

	// pickup* for the one player is holding 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PickUp)
	APickUp* MyPickUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Creature)
	ACreature* MyCreature;

	void UpdateAnimation();

	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* PickUpAnimation;

	// The animation to play while idle 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	// The animation to play while idle 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TSubobjectPtr<class UBoxComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float PowerLevel;

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Play eat sound"))
	virtual void PlayEatSound();

	//UFUNCTION(BlueprintCallable, Category = PowerUp)	
	void PowerUp(float amount);
};
