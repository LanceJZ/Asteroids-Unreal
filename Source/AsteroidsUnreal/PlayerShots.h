#pragma once

#include "Shot.h"
#include "AsteroidsHUD.h"
#include "GameFramework/Actor.h"
#include "PlayerShots.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API APlayerShots : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APlayerShots();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere)
	class USoundBase* FireSound;

	AShot* aShots[4];

	uint8 NumberOfPlayerShotsFired;
	uint32 Score;

	void FireShot(FVector location, FRotator rotation);
	void ShotHit(uint8 shot);
	void ScoredHit(uint16 points, uint8 shot);
	void UpdateScore(uint32 points);
};
