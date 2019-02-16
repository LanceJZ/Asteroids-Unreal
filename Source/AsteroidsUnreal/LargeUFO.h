#pragma once

#include "Shot.h"
#include "GameFramework/Actor.h"
#include "LargeUFO.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API ALargeUFO : public AActor, public Common
{
	GENERATED_BODY()

	//Our UFO Mesh Component
	class UStaticMeshComponent* UFOMeshComponent;

	/** Handle for efficient management of TimerExpired timer */
	FTimerHandle TimerHandle_VectorTimerExpired;
	FTimerHandle TimerHandle_FireTimerExpired;

public:	
	// Sets default values for this actor's properties
	ALargeUFO(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Returns RockMeshComponent sub object **/
	FORCEINLINE class UStaticMeshComponent* GetRockMeshComponent() const { return UFOMeshComponent; }

	UFUNCTION()
	void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ChangeVector();
	void FireShot();

	bool bFromRightSide;
	bool bChangeVector;
	bool bHitOtherSide;
	float VectorChangeRate;
	float XRotation;
	FVector ERotation;
	AShot* pShot;
};
