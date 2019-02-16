#pragma once
#include "Common.h"
#include "Shot.h"
#include "PlayerShip.h"
#include "PlayerShots.h"
#include "PlayerShipDisplay.h"
#include "PlayerClearToSpawn.h"
#include <vector>
#include "AsteroidsSpawner.h"
#include "UFOSpawner.h"
#include "GameFramework/Pawn.h"
#include "GameSpawner.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API AGameSpawner : public APawn, public Common
{
	GENERATED_BODY()
	
	// Private
private:
	APlayerShip* pPlayerShip;	
	AAsteroidsSpawner* pASpawner;
	AUFOSpawner* pUFOSpawner;
	APlayerClearToSpawn* pClearSphere;
	std::vector<APlayerShipDisplay*> vPlayerDisplay;
	
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	uint8 Lives;
	bool bCanFire;

	void ActivatePlayer();
	void UpdateDisplay(uint8 lives);
	//void ScoredHit(uint16 points, uint8 shot);
	void PlayerShipHit();
	void ShotTimerExpired();

public:	
	// Sets default values for this actor's properties
	AGameSpawner(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere)
	float FireRate;
	APlayerShots* pPlayerShot;

	void NewGame();

	//Input functions
	void RotateRight();
	void RotateLeft();
	void StopRotation();
	void Thrust();
	void StopThrust();
	/* Fire a shot in the specified direction */
	void FireShot();
	void Hyperspace();
	bool bGameOver;
};
