#pragma once

#include "GameFramework/Actor.h"
#include "PlayerClearToSpawn.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API APlayerClearToSpawn : public AActor
{
	GENERATED_BODY()
	
	//USceneComponent* ShipModelComponent;
	class UStaticMeshComponent* MeshComponent;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ClearTimerExpired;

public:	
	// Sets default values for this actor's properties
	APlayerClearToSpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	/** Returns Sphere sub object **/
	FORCEINLINE class UStaticMeshComponent* GetRockMeshComponent() const { return MeshComponent; }

	UFUNCTION()
		void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool bIsClear;
	uint16 NumberOfHits;
	AActor* ActorHit;

	void Disable();
	void Clear();
};
