#pragma once
#include "RockMaster.h"
#include "PlayerShip.h"
#include "PlayerShots.h"
#include "UFOSpawner.h"
#include <vector>
#include "GameFramework/Actor.h"
#include "AsteroidsSpawner.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API AAsteroidsSpawner : public AActor
{
	GENERATED_BODY()

	APlayerShip* pPlayerShip;
	APlayerShots* pPlayerShots;
	AUFOSpawner* pUFOs;	

public:
	// Sets default values for this actor's properties
	AAsteroidsSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	std::vector<ARockMaster*> vLargeRocks;
	std::vector<ARockMaster*> vMedRocks;
	std::vector<ARockMaster*> vSmallRocks;

	void PlayerPointer(APlayerShip* playerPointer);
	void PlayerShotPointer(APlayerShots* playerShotsPointer);
	void UFOsPointer(AUFOSpawner* theUFOsPointer);
	void SpawnRocks(int numberOfRocks);
	void NewWave();
	void CheckRockHit();
	void NewGame();

	void LargeRockHit(size_t rock);
	void MedRockHit(size_t rock);
	void SmallRockHit(size_t rock);

	uint16 Wave;
};
