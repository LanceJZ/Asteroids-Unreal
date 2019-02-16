#pragma once

#include "GameFramework/Actor.h"
#include "PlayerShip.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API APlayerShip : public AActor
{
	GENERATED_BODY()

	//USceneComponent* ShipModelComponent;
	class UStaticMeshComponent* ShipMeshComponent;
	
public:
	// Sets default values for this pawn's properties
	APlayerShip();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(Category = Camera, EditAnywhere)
	AActor* ViewCamera;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere)
	class USoundBase* FireSound;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere)
	float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere)
	float MoveSpeed;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere)
	float RotateSpeed;

	//Input functions
	void RotateRight();
	void RotateLeft();
	void StopRotation();
	void Thrust();
	void StopThrust();
	void Hyperspace();

	//Input variables
	FRotator RotateVelocity;
	FVector Velocity;
	FVector Acceleration;
	uint32 Score;
	bool bThrust;
	bool bHit;
	bool bHitObject;
	bool bHitCounted;
	bool bShipSpawned;

	void ThrustOn();
	void CheckVelocity();
	void SpawnShip();
	void ShipHit(uint16 points);
	void Disable();

	/** Returns ShipMeshComponent sub object **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }

	// Collision Detection
	UFUNCTION()
	void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Functions for other classes.
	AActor* ActorHit;

};
