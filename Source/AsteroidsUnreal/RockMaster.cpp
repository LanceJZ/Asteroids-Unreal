#include "AsteroidsUnreal.h"
#include "RockMaster.h"


// Sets default values
ARockMaster::ARockMaster(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Find static mesh.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockMesh(TEXT("/Game/Asteroids/Asteroid.Asteroid")); //StaticMesh'/Game/Asteroids/Asteroid.Asteroid'
	// Create the mesh component
	RockMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"));
	RockMeshComponent->SetStaticMesh(RockMesh.Object);
	//RockMeshComponent->SetCollisionProfileName("Rock");
	RockMeshComponent->bGenerateOverlapEvents = true;
	//RockMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ARockMaster::OnOverlap);
	//RockMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ARockMaster::OnEndOverlap);
	RootComponent = RockMeshComponent;
	RockMeshComponent->SetMobility(EComponentMobility::Movable);
	
	bHitObject = false;
	Velocity.ZeroVector;
}

// Called when the game starts or when spawned
void ARockMaster::BeginPlay()
{
	Super::BeginPlay();

	AActor::SetActorLabel("Rock Master");
	
	if (FMath::RandRange(0, 10) > 5)
	{
		Velocity.X = FMath::RandRange(MinX, MaxX);
	}
	else
	{
		Velocity.X = FMath::RandRange(-MaxX, -MinX);
	}

	if (FMath::RandRange(0, 10) > 5)
	{
		Velocity.Y = FMath::RandRange(MinY, MaxY);
	}
	else
	{
		Velocity.Y = FMath::RandRange(-MaxY, -MinY);
	}

	RotateVelocity.Yaw = FMath::RandRange(-RVY, RVY);
	RotateVelocity.Pitch = FMath::RandRange(-RVP, RVP);
}

// Called every frame
void ARockMaster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	SetActorLocation(Common::CheckEdge(GetActorLocation() + Velocity * DeltaTime));
	SetActorRotation(GetActorRotation() + RotateVelocity * DeltaTime);
}

void ARockMaster::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		bHitObject = true;
		ActorHit = OtherActor;
	}
}

void ARockMaster::OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		bHitObject = false;
		ActorHit = NULL;
	}
}