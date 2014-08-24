

#include "YOLA.h"
#include "MyAnt.h"
#include "MyPlayerController.h"


AMyPlayerController::AMyPlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	ToLocationCounter = 0.0f;
	MovingToLocation = false;
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		
		MoveToMouseCursor();
	}

	if (MovingToLocation)
	{
		ToLocationCounter += (DeltaTime * .1);
		SetNewMoveDestination();
	}
	
}

void AMyPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Bind actions
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMyPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMyPlayerController::OnSetDestinationReleased);
}

void AMyPlayerController::MoveToMouseCursor()
{
	if (!bIsPaused)
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		APawn* const Pawn = GetPawn();
		//float const Distance = FVector::Dist(DestinationLocation, Pawn->GetActorLocation());
		
		if (Hit.bBlockingHit)
		{
			DestinationLocation = Hit.ImpactPoint;
			// We hit something, move there
			SetNewMoveDestination();
			MovingToLocation = true;
			
		}
	}
}


void AMyPlayerController::SetNewMoveDestination()
{
	if (!bIsPaused)
	{
		
		AMyAnt* MyAnt = Cast<AMyAnt>(UGameplayStatics::GetPlayerCharacter(this, 0));
		APawn* const Pawn = GetPawn();
		if (Pawn)
		{
				MyAnt->SetActorLocation(FMath::Lerp(MyAnt->GetActorLocation(), FVector(DestinationLocation.X, DestinationLocation.Y, MyAnt->GetActorLocation().Z), ToLocationCounter),true);
				if (ToLocationCounter >= 1.0f)
				{
					MovingToLocation = false;
					ToLocationCounter = 0;
				}
			// We need to issue move command only if far enough in order for walk animation to play correctly
			//if (NavSys && (Distance > 120.0f))
			//{
			//	NavSys->SimpleMoveToLocation(this, DestLocation);
			//}
		}
	}
}

void AMyPlayerController::OnSetDestinationPressed()
{
	ToLocationCounter = 0;
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMyPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AMyPlayerController::PausePlayer()
{

	bIsPaused = true;
	
}

void AMyPlayerController::MovePlayerToLocation(const FVector Location)
{

}

