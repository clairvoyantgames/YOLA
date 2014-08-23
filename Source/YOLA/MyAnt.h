

#pragma once

#include "PaperCharacter.h"
#include "GameFramework/Character.h"
#include "PickUp.h"
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
	bool bBroLifts;
	// pickup* for the one player is holding 
	APickUp* MyPickUp;
	
};