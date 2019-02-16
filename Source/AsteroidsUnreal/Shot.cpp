#include "AsteroidsUnreal.h"
#include "Shot.h"
#include "Common.h"

// Sets default values
AShot::AShot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Projectile.Projectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);	
	ProjectileMesh->AttachTo(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->bGenerateOverlapEvents = true;
	//ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AShot::OnOverlap);
	
	RootComponent = ProjectileMesh;

	// Die after X seconds by default
	InitialLifeSpan = 1.4f;
	bHitObject = false;
	Velocity.ZeroVector;
}

// Called when the game starts or when spawned
void AShot::BeginPlay()
{
	Super::BeginPlay();
	InitialLifeSpan = 1.4f;
	bHitObject = false;
	AActor::SetActorLabel("TheShot");

	FVector AngleInRad = GetActorRotation().Euler();
	float ZAngleInRad = FMath::DegreesToRadians(AngleInRad.Z) + 1.57f;

	Velocity.X = FMath::Cos(ZAngleInRad);
	Velocity.Y = FMath::Sin(ZAngleInRad);
	Velocity.Z = 0;

	Velocity *= 100;
}

// Called every frame
void AShot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	SetActorLocation(Common::CheckEdge(GetActorLocation() + Velocity * DeltaTime));
}

void AShot::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{	
	if ((OtherActor != NULL) && (OtherActor != this))
	{		
		bHitObject = true;
		ActorHit = OtherActor;
	}
}

void AShot::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		bHitObject = false;
		ActorHit = NULL;
	}
}
