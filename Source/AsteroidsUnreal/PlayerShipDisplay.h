#pragma once

#include "GameFramework/Actor.h"
#include "PlayerShipDisplay.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API APlayerShipDisplay : public AActor
{
	GENERATED_BODY()

	//USceneComponent* ShipModelComponent;
	class UStaticMeshComponent* ShipMeshComponent;

public:
	// Sets default values for this pawn's properties
	APlayerShipDisplay();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Returns ShipMeshComponent sub object **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }

};
