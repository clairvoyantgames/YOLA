

#include "YOLA.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "MyAnt.h"


AMyAnt::AMyAnt(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create a camera boom...
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUseControllerViewRotation = false; // Camera does not rotate relative to arm
	bBroLifts = false;

	CollisionComp = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionComp"));
	CollisionComp->InitBoxExtent(FVector(150));
	CollisionComp->AttachTo(RootComponent);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComp->bGenerateOverlapEvents = true;

	CapsuleComponent->SetCapsuleHalfHeight(75);
	CapsuleComponent->SetCapsuleRadius(75);
	//Sprite = PCIP.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("TheSprite"));
}

void AMyAnt::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	
	// Bind actions
	InputComponent->BindAction("PickUp", IE_Pressed, this, &AMyAnt::PickUp);
}

void AMyAnt::PickUp()
{
	// if player is not lifting then lift something
	if (!bBroLifts)
	{
		// pick up whatever is in front of it 
		TArray<AActor*> OverlappingActors;
		CollisionComp->GetOverlappingActors(OverlappingActors);
		if (OverlappingActors.Num() > 0)
		{
			for (int32 x = 0; x < OverlappingActors.Num(); x++)
			{
				APickUp* overlappedPickUp = Cast<APickUp>(OverlappingActors[x]);
				if (overlappedPickUp && overlappedPickUp->GetPickUpStatus() != EPickUpStatus::EPickedUp)
				{
					MyPickUp = overlappedPickUp;
					MyPickUp->PickUp();
					bBroLifts = true;
					//UpdateAnimation();
					break;
				}
			}
		}
	}
	else
	{

		// player has something so drop it
		MyPickUp->Drop();
		bBroLifts = false;
	}
}

void AMyAnt::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeed = PlayerVelocity.Size();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeed > 0.0f) ? RunningAnimation : IdleAnimation;
	//Sprite->SetFlipbook(DesiredAnimation);
	Sprite->SetFlipbook(DesiredAnimation);
}