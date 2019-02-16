#include "AsteroidsUnreal.h"
#include "UFOSpawner.h"


// Sets default values
AUFOSpawner::AUFOSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUFOSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnRate = 35;

	ResetTimer();
}

// Called every frame
void AUFOSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	CheckUFOHit();
}

void AUFOSpawner::PlayerPointer(APlayerShip* playerPointer)
{
	pPlayerShip = playerPointer;
}

void AUFOSpawner::PlayerShotPointer(APlayerShots* playerShotPointer)
{
	pPlayerShot = playerShotPointer;
}

void AUFOSpawner::ResetTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UFOTimerExpired, this, &AUFOSpawner::SpawnUFO, FMath::RandRange(SpawnRate / 1.125f, SpawnRate));
}

void AUFOSpawner::SpawnUFO()
{
	float spawnPercent = float(pow(0.985, (SpawnCount * 2) / Wave + 2));
	SpawnCount++;

	if (FMath::RandRange(1, 100) < spawnPercent * 100)
	{
		pUFOL = GetWorld()->SpawnActor<ALargeUFO>();		
	}
	else
	{
		pUFOS = GetWorld()->SpawnActor<ASmallUFO>();		
	}
}

void AUFOSpawner::CheckUFOHit()
{
	if (pShot != NULL && pPlayerShip != NULL)
	{
		if (pShot->bHitObject != NULL)
		{
			if (pShot->bHitObject)
			{
				if (pShot->ActorHit == pPlayerShip)
				{
					pPlayerShip->ShipHit(0);
					pShot->bHitObject = false;
					pShot->Destroy();
					pShot = NULL;
				}
			}
		}
	}
	
	if (pUFOL != NULL)
	{
		pShot = pUFOL->pShot;

		if (pUFOL->bHitObject)
		{
			for (int shot = 0; shot < 4; shot++)
			{
				if (pPlayerShot->aShots[shot] != NULL)
				{
					if (pUFOL->ActorHit == pPlayerShot->aShots[shot])
					{
						pPlayerShot->ScoredHit(200, shot);
						pUFOL->Destroy();
						pUFOL = NULL;
						ResetTimer();
						break;
					}
				}
			}

			if (pPlayerShip != NULL && pUFOL != NULL)
			{
				if (pUFOL->ActorHit == pPlayerShip)
				{
					pPlayerShip->ShipHit(200);
					pUFOL->Destroy();
					pUFOL = NULL;
					ResetTimer();
				}
			}
		}

		if (pUFOL != NULL)
		{
			if (pUFOL->bHitOtherSide)
			{
				pUFOL->Destroy();
				pUFOL = NULL;
				ResetTimer();
			}
		}
	}

	if (pUFOS != NULL)
	{
		pShot = pUFOS->pShot;

		if (pUFOS->bHitObject)
		{
			for (int shot = 0; shot < 4; shot++)
			{
				if (pPlayerShot->aShots[shot] != NULL)
				{
					if (pUFOS->ActorHit == pPlayerShot->aShots[shot])
					{
						pPlayerShot->ScoredHit(1000, shot);
						pUFOS->Destroy();
						pUFOS = NULL;
						ResetTimer();
						break;
					}
				}
			}

			if (pPlayerShip != NULL && pUFOS != NULL)
			{
				if (pUFOS->ActorHit == pPlayerShip)
				{
					pPlayerShip->ShipHit(1000);
					pUFOS->Destroy();
					pUFOS = NULL;
					ResetTimer();
				}
			}
		}

		if (pUFOS != NULL)
		{
			if (pUFOS->bHitOtherSide)
			{
				pUFOS->Destroy();
				pUFOS = NULL;
				ResetTimer();
			}
		}
	}
}

void AUFOSpawner::NewGame()
{
	if (pUFOL != NULL)
	{
		if (pUFOL->pShot != NULL)
		{
			pUFOL->pShot->Destroy();
			pUFOL->pShot = NULL;
		}

		pUFOL->Destroy();
		pUFOL = NULL;
	}

	if (pUFOS != NULL)
	{
		if (pUFOS->pShot != NULL)
		{
			pUFOS->pShot->Destroy();
			pUFOS->pShot = NULL;
		}

		pUFOS->Destroy();
		pUFOS = NULL;
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UFOTimerExpired, this, &AUFOSpawner::SpawnUFO, FMath::RandRange(SpawnRate / 1.125f, SpawnRate));
	SpawnCount = 0;
}