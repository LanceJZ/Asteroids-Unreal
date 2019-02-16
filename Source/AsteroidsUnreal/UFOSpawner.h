#pragma once
#include "PlayerShip.h"
#include "PlayerShots.h"
#include "LargeUFO.h"
#include "SmallUFO.h"
#include "Shot.h"
#include "GameFramework/Actor.h"
#include "UFOSpawner.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API AUFOSpawner : public AActor
{
	GENERATED_BODY()
	
	/** Handle for efficient management of TimerExpired timer */
	FTimerHandle TimerHandle_UFOTimerExpired;
	APlayerShip* pPlayerShip;
	APlayerShots* pPlayerShot;

public:	
	// Sets default values for this actor's properties
	AUFOSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void PlayerPointer(APlayerShip* playerPointer);
	void PlayerShotPointer(APlayerShots* playerShotPointer);

	void CheckUFOHit();
	void SpawnUFO();
	void NewGame();
	void ResetTimer();

	ALargeUFO* pUFOL;
	ASmallUFO* pUFOS;
	AShot* pShot;

	float SpawnRate;
	uint16 SpawnCount;
	uint16 Wave;
};
