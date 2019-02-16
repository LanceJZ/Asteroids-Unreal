#include "AsteroidsUnreal.h"
#include "GameSpawner.h"

// Sets default values
AGameSpawner::AGameSpawner(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bGameOver = true;
	FireRate = 0.0314f;
}

// Called when the game starts or when spawned
void AGameSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* const World = GetWorld();
	
	pPlayerShot = World->SpawnActor<APlayerShots>();
	pASpawner = World->SpawnActor<AAsteroidsSpawner>();
	pUFOSpawner = World->SpawnActor<AUFOSpawner>();
	pASpawner->UFOsPointer(pUFOSpawner);
	pUFOSpawner->PlayerPointer(NULL);
	pUFOSpawner->PlayerShotPointer(pPlayerShot);
	pASpawner->PlayerPointer(NULL);
	pASpawner->PlayerShotPointer(pPlayerShot);
}

// Called every frame
void AGameSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (pPlayerShip != NULL)
	{
		if (pPlayerShip->IsPendingKill())
		{
			pPlayerShip = NULL;
		}

		PlayerShipHit();
	}
	else if (!bGameOver)
	{
		ActivatePlayer();
	}
}

// Called to bind functionality to input
void AGameSpawner::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);

	InputComponent->BindAction("NewGame", IE_Pressed, this, &AGameSpawner::NewGame);
	InputComponent->BindAction("RotateRight", IE_Pressed, this, &AGameSpawner::RotateRight);
	InputComponent->BindAction("RotateLeft", IE_Pressed, this, &AGameSpawner::RotateLeft);
	InputComponent->BindAction("RotateRight", IE_Released, this, &AGameSpawner::StopRotation);
	InputComponent->BindAction("RotateLeft", IE_Released, this, &AGameSpawner::StopRotation);
	InputComponent->BindAction("Thrust", IE_Pressed, this, &AGameSpawner::Thrust);
	InputComponent->BindAction("Thrust", IE_Released, this, &AGameSpawner::StopThrust);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AGameSpawner::FireShot);
	InputComponent->BindAction("Hyperspace", IE_Pressed, this, &AGameSpawner::Hyperspace);
}

void AGameSpawner::ActivatePlayer()
{
	if (pClearSphere->bIsClear)
	{
		pPlayerShip = GetWorld()->SpawnActor<APlayerShip>(FVector(0, 0, 100), FRotator(0, 0, 0));
		pPlayerShip->SpawnShip();
		pClearSphere->Disable();
		pClearSphere->Destroy();
		pClearSphere = NULL;
		pASpawner->PlayerPointer(pPlayerShip);
		pUFOSpawner->PlayerPointer(pPlayerShip);		
	}
}

void AGameSpawner::NewGame()
{
	if (bGameOver)
	{
		Lives = 4;
		pPlayerShot->Score = 0;
		
		pPlayerShip = GetWorld()->SpawnActor<APlayerShip>(FVector(0, 0, 100), FRotator(0, 0, 0));
		pASpawner->PlayerPointer(pPlayerShip);
		pUFOSpawner->PlayerPointer(pPlayerShip);
		pASpawner->NewGame();
		pUFOSpawner->NewGame();
		bGameOver = false;
		UpdateDisplay(Lives);
		pPlayerShip->SpawnShip();
		bCanFire = true;
	}
}

void AGameSpawner::UpdateDisplay(uint8 lives)
{
	if (vPlayerDisplay.size() > 0)
	{
		for (size_t ship = 0; ship < vPlayerDisplay.size(); ship++)
		{
			vPlayerDisplay.at(ship)->Destroy();
		}

		vPlayerDisplay.clear();
	}

	for (size_t ship = 0; ship < lives; ship++)
	{
		vPlayerDisplay.push_back(GetWorld()->SpawnActor<APlayerShipDisplay>(FVector(18 - (ship * 1), 10, 180), FRotator(0, 90, 0)));
	}
}

void AGameSpawner::PlayerShipHit()
{
	if (pPlayerShip->bHit)
	{
		Lives--;

		UE_LOG(LogTemp, Warning, TEXT("Player was hit, and has %d lives left"), Lives);

		UpdateDisplay(Lives);
		pPlayerShot->UpdateScore(pPlayerShip->Score);
		pPlayerShip->Disable();
		pPlayerShip->Destroy();
		pPlayerShip = NULL;
		pASpawner->PlayerPointer(NULL);
		pUFOSpawner->PlayerPointer(NULL);

		if (Lives < 1)
			bGameOver = true;
		else
			pClearSphere = GetWorld()->SpawnActor<APlayerClearToSpawn>(FVector(0, 0, 100), FRotator(0, 0, 0));
	}
}

//Input functions
void AGameSpawner::RotateRight()
{
	if (pPlayerShip != NULL)
	{
		pPlayerShip->RotateRight();
	}
}

void AGameSpawner::RotateLeft()
{
	if (pPlayerShip != NULL)
	{
		pPlayerShip->RotateLeft();
	}
}

void AGameSpawner::StopRotation()
{
	if (pPlayerShip != NULL)
	{
		pPlayerShip->StopRotation();
	}
}

void AGameSpawner::Thrust()
{
	if (pPlayerShip != NULL)
	{
		pPlayerShip->Thrust();
	}
}

void AGameSpawner::StopThrust()
{
	if (pPlayerShip != NULL)
	{
		pPlayerShip->StopThrust();
	}
}

void AGameSpawner::FireShot()
{
	if (pPlayerShip != NULL)
	{
		if (bCanFire)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AGameSpawner::ShotTimerExpired, FireRate);
			pPlayerShot->FireShot(pPlayerShip->GetActorLocation(), pPlayerShip->GetActorRotation());
			bCanFire = false;
		}
	}
}

void AGameSpawner::ShotTimerExpired()
{
	bCanFire = true;
}

void AGameSpawner::Hyperspace()
{
	if (pPlayerShip != NULL)
	{
		pPlayerShip->Hyperspace();
	}
}
