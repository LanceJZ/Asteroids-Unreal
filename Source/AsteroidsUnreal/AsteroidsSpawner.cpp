#include "AsteroidsUnreal.h"
#include "AsteroidsSpawner.h"

// Sets default values
AAsteroidsSpawner::AAsteroidsSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAsteroidsSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	NewWave();
}

// Called every frame
void AAsteroidsSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	CheckRockHit();

	if (vLargeRocks.size() + vMedRocks.size() + vSmallRocks.size() == 0)
		NewWave();
}

void AAsteroidsSpawner::PlayerPointer(APlayerShip* playerPointer)
{
	pPlayerShip = playerPointer;
}

void AAsteroidsSpawner::PlayerShotPointer(APlayerShots* playerShotsPointer)
{
	pPlayerShots = playerShotsPointer;
}

void AAsteroidsSpawner::UFOsPointer(AUFOSpawner* theUFOsPointer)
{
	pUFOs = theUFOsPointer;
}

void AAsteroidsSpawner::SpawnRocks(int numberOfRocks)
{	
	// Spawn large rocks
	for (size_t rock = 0; rock < numberOfRocks; rock++)
	{
		vLargeRocks.push_back(GetWorld()->SpawnActor<ARockMaster>(FVector(105, FMath::RandRange(-50, 50), 100), FRotator(0, 0, 0)));
		vLargeRocks.at(rock)->SetActorRelativeScale3D(FVector(2, 2, 2));
		vLargeRocks.at(rock)->MaxX = 8.5;
		vLargeRocks.at(rock)->MinX = 4.5;
		vLargeRocks.at(rock)->MaxY = 7.5;
		vLargeRocks.at(rock)->MinY = 3.5;
		vLargeRocks.at(rock)->RVY = 16.8;
		vLargeRocks.at(rock)->RVP = 15.7;
		vLargeRocks.at(rock)->BeginPlay();
	}
}

void AAsteroidsSpawner::NewWave()
{
	Wave++;

	SpawnRocks((Wave * 2) + 2);
	pUFOs->Wave = Wave;
}

void AAsteroidsSpawner::LargeRockHit(size_t rock)
{
	UWorld* const World = GetWorld();
	int16 RockCount = vMedRocks.size();

	for (size_t newRock = RockCount; newRock < RockCount + 2; newRock++)
	{
		vMedRocks.push_back(World->SpawnActor<ARockMaster>(vLargeRocks.at(rock)->GetActorLocation(), vLargeRocks.at(rock)->GetActorRotation()));		
		vMedRocks.at(newRock)->SetActorRelativeScale3D(FVector(1.4f, 1.4f, 1.4f));
		vMedRocks.at(newRock)->MaxX = 8.5;
		vMedRocks.at(newRock)->MinX = 15.5;
		vMedRocks.at(newRock)->MaxY = 12.5;
		vMedRocks.at(newRock)->MinY = 6.5;
		vMedRocks.at(newRock)->RVY = 28.8;
		vMedRocks.at(newRock)->RVP = 26.7;
		vMedRocks.at(newRock)->BeginPlay();
	}

	vLargeRocks.at(rock)->Destroy();
	vLargeRocks.erase(vLargeRocks.begin() + rock);
}

void AAsteroidsSpawner::MedRockHit(size_t rock)
{
	UWorld* const World = GetWorld();
	int16 RockCount = vSmallRocks.size();

	for (size_t newRock = RockCount; newRock < RockCount + 2; newRock++)
	{
		vSmallRocks.push_back(World->SpawnActor<ARockMaster>(vMedRocks.at(rock)->GetActorLocation(), vMedRocks.at(rock)->GetActorRotation()));		
		vSmallRocks.at(newRock)->SetActorRelativeScale3D(FVector(0.9f, 0.9f, 0.9f));
		vSmallRocks.at(newRock)->MaxX = 35.5;
		vSmallRocks.at(newRock)->MinX = 12.5;
		vSmallRocks.at(newRock)->MaxY = 30.5;
		vSmallRocks.at(newRock)->MinY = 10.5;
		vSmallRocks.at(newRock)->RVY = 60.8;
		vSmallRocks.at(newRock)->RVP = 68.7;
		vSmallRocks.at(newRock)->BeginPlay();
	}

	vMedRocks.at(rock)->Destroy();
	vMedRocks.erase(vMedRocks.begin() + rock);
}

void AAsteroidsSpawner::SmallRockHit(size_t rock)
{
	vSmallRocks.at(rock)->Destroy();
	vSmallRocks.erase(vSmallRocks.begin() + rock);
}

void AAsteroidsSpawner::CheckRockHit()
{
	UWorld* const World = GetWorld();

	for (size_t rock = 0; rock < vLargeRocks.size(); rock++)
	{
		if (vLargeRocks.at(rock)->bHitObject)
		{
			for (int shot = 0; shot < 4; shot++)
			{
				if (pPlayerShots->aShots[shot] != NULL)
				{
					if (vLargeRocks.at(rock)->ActorHit == pPlayerShots->aShots[shot])
					{
						pPlayerShots->ScoredHit(20, shot);
						LargeRockHit(rock);
						return;
					}
				}
			}

			if (pPlayerShip != NULL)
			{
				if (vLargeRocks.at(rock)->ActorHit == pPlayerShip && pPlayerShip->bShipSpawned)
				{
					pPlayerShip->ShipHit(20);
					pPlayerShip = NULL;
					LargeRockHit(rock);
					return;
				}
			}

			if (pUFOs->pUFOL != NULL)
			{
				if (vLargeRocks.at(rock)->ActorHit == pUFOs->pUFOL)
				{
					LargeRockHit(rock);
					pUFOs->pUFOL->Destroy();
					pUFOs->pUFOL = NULL;
					pUFOs->ResetTimer();
					return;
				}
			}

			if (pUFOs->pUFOS != NULL)
			{
				if (vLargeRocks.at(rock)->ActorHit == pUFOs->pUFOS)
				{
					LargeRockHit(rock);
					pUFOs->pUFOS->Destroy();
					pUFOs->pUFOS = NULL;
					pUFOs->ResetTimer();
					return;
				}
			}

			if (pUFOs->pShot != NULL)
			{
				if (vLargeRocks.at(rock)->ActorHit == pUFOs->pShot)
				{
					LargeRockHit(rock);
					pUFOs->pShot->Destroy();
					pUFOs->pShot = NULL;
					return;
				}
			}
		}
	}

	for (size_t rock = 0; rock < vMedRocks.size(); rock++)
	{
		if (vMedRocks.at(rock)->bHitObject)
		{
			for (int shot = 0; shot < 4; shot++)
			{
				if (pPlayerShots->aShots[shot] != NULL)
				{
					if (vMedRocks.at(rock)->ActorHit == pPlayerShots->aShots[shot])
					{
						pPlayerShots->ScoredHit(50, shot);
						MedRockHit(rock);
						return;
					}
				}
			}

			if (pPlayerShip != NULL)
			{
				if (vMedRocks.at(rock)->ActorHit == pPlayerShip && pPlayerShip->bShipSpawned)
				{
					pPlayerShip->ShipHit(50);
					pPlayerShip = NULL;
					MedRockHit(rock);
					return;
				}
			}

			if (pUFOs->pUFOL != NULL)
			{
				if (vMedRocks.at(rock)->ActorHit == pUFOs->pUFOL)
				{
					MedRockHit(rock);
					pUFOs->pUFOL->Destroy();
					pUFOs->pUFOL = NULL;
					pUFOs->ResetTimer();
					return;
				}
			}

			if (pUFOs->pUFOS != NULL)
			{
				if (vMedRocks.at(rock)->ActorHit == pUFOs->pUFOS)
				{
					MedRockHit(rock);
					pUFOs->pUFOS->Destroy();
					pUFOs->pUFOS = NULL;
					pUFOs->ResetTimer();
					return;
				}
			}

			if (pUFOs->pShot != NULL)
			{
				if (vMedRocks.at(rock)->ActorHit == pUFOs->pShot)
				{
					MedRockHit(rock);
					pUFOs->pShot->Destroy();
					pUFOs->pShot = NULL;
					pUFOs->ResetTimer();
					return;
				}
			}
		}
	}

	for (size_t rock = 0; rock < vSmallRocks.size(); rock++)
	{
		if (vSmallRocks.at(rock)->bHitObject)
		{
			for (int shot = 0; shot < 4; shot++)
			{
				if (pPlayerShots->aShots[shot] != NULL)
				{
					if (vSmallRocks.at(rock)->ActorHit == pPlayerShots->aShots[shot])
					{
						pPlayerShots->ScoredHit(100, shot);
						SmallRockHit(rock);
						return;
					}
				}
			}

			if (pPlayerShip != NULL)
			{
				if (vSmallRocks.at(rock)->ActorHit == pPlayerShip && pPlayerShip->bShipSpawned)
				{
					pPlayerShip->ShipHit(100);
					pPlayerShip = NULL;
					SmallRockHit(rock);
					return;
				}
			}
			
			if (pUFOs->pUFOL != NULL)
			{
				if (vSmallRocks.at(rock)->ActorHit == pUFOs->pUFOL)
				{
					SmallRockHit(rock);
					pUFOs->pUFOL->Destroy();
					pUFOs->pUFOL = NULL;
					pUFOs->ResetTimer();
					return;
				}
			}

			if (pUFOs->pUFOS != NULL)
			{
				if (vSmallRocks.at(rock)->ActorHit == pUFOs->pUFOS)
				{
					SmallRockHit(rock);
					pUFOs->pUFOS->Destroy();
					pUFOs->pUFOS = NULL;
					pUFOs->ResetTimer();
					return;
				}
			}

			if (pUFOs->pShot != NULL)
			{
				if (vSmallRocks.at(rock)->ActorHit == pUFOs->pShot)
				{
					SmallRockHit(rock);
					pUFOs->pShot->Destroy();
					pUFOs->pShot = NULL;
					pUFOs->ResetTimer();
					return;
				}
			}
		}
	}
}

void AAsteroidsSpawner::NewGame()
{
	for (size_t rock = 0; rock < vLargeRocks.size(); rock++)
	{
		vLargeRocks.at(rock)->Destroy();
	}

	vLargeRocks.clear();

	for (size_t rock = 0; rock < vMedRocks.size(); rock++)
	{
		vMedRocks.at(rock)->Destroy();
	}

	vMedRocks.clear();

	for (size_t rock = 0; rock < vSmallRocks.size(); rock++)
	{
		vSmallRocks.at(rock)->Destroy();
	}

	vSmallRocks.clear();

	Wave = 0;
	NewWave();
}