#pragma once
#include "Common.h"
#include "GameFramework/Actor.h"
#include "Shot.generated.h"
class UStaticMeshComponent;

UCLASS(config = Game)
class ASTEROIDSUNREAL_API AShot : public AActor, public Common
{
	GENERATED_BODY()
	
	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	FVector Velocity;

public:	
	// Sets default values for this actor's properties
	AShot(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	/** Returns ProjectileMesh sub object **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }

	AActor* ActorHit;
	bool bHitObject;
	bool bHitCounted;

};
