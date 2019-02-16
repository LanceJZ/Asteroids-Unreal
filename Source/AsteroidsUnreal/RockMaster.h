#pragma once
#include "Common.h"
#include "GameFramework/Actor.h"
#include "RockMaster.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API ARockMaster : public AActor, public Common
{
	GENERATED_BODY()

private:
	/** Returns RockMeshComponent sub object **/
	FORCEINLINE class UStaticMeshComponent* GetRockMeshComponent() const { return RockMeshComponent; }

public:	
	// Sets default values for this actor's properties
	ARockMaster(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Our rock Mesh Component
	class UStaticMeshComponent* RockMeshComponent;


	UFUNCTION()
		void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float MaxX;
	float MinX;
	float MaxY;
	float MinY;
	float RVY;
	float RVP;
};
