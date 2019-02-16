#include "AsteroidsUnreal.h"
#include "PlayerShots.h"
#include "AsteroidsHUD.h"

// Sets default values
APlayerShots::APlayerShots()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumberOfPlayerShotsFired = 0;

	// HUD BP Blueprint'/Game/HUDBP.HUDBP'
	
}

// Called when the game starts or when spawned
void APlayerShots::BeginPlay()
{
	Super::BeginPlay();
	NumberOfPlayerShotsFired = 0;
}

// Called every frame
void APlayerShots::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APlayerShots::UpdateScore(uint32 points)
{
	Score += points;
}

void APlayerShots::ScoredHit(uint16 points, uint8 shot)
{
	UpdateScore(points);
	aShots[shot]->Destroy();
	aShots[shot] = NULL;
	NumberOfPlayerShotsFired--;

	UE_LOG(LogTemp, Warning, TEXT("Player Score is %d"), Score);
}

void APlayerShots::FireShot(FVector location, FRotator rotation)
{
	FVector FireDirection;
	FVector AngleInDeg = rotation.Euler();
	float ZAngleInRad = FMath::DegreesToRadians(AngleInDeg.Z);

	FireDirection.X = FMath::Cos(ZAngleInRad) * 2.5f;
	FireDirection.Y = FMath::Sin(ZAngleInRad) * 2.5f;
	FireDirection.Z = 0;

	for (int shot = 0; shot < 4; shot++)
	{
		if (aShots[shot] != NULL)
		{
			if (aShots[shot]->IsPendingKill())
			{
				NumberOfPlayerShotsFired--;
				aShots[shot] = NULL;
			}
		}
	}

	for (int shot = 0; shot < 4; shot++)
	{
		if (aShots[shot] == NULL)
		{
			if (NumberOfPlayerShotsFired < 4)
			{
				// spawn the projectile
				aShots[shot] = GetWorld()->SpawnActor<AShot>(location + FireDirection, rotation - FRotator(0, 90, 0));
				NumberOfPlayerShotsFired++;
				break;
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, location);
	}
}