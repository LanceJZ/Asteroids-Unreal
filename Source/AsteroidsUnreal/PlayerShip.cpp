#include "AsteroidsUnreal.h"
#include "PlayerShip.h"
#include "TimerManager.h"
#include "Common.h"

// Sets default values
APlayerShip::APlayerShip()	
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Player/CorvetteShip.CorvetteShip"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	AActor::SetActorLabel("ThePlayerShip");
	FireRate = 0.0314f;
	MoveSpeed = 60.0f;
	RotateSpeed = 180.0f;
	bHit = false;
	bShipSpawned = false;
}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Lance is god here."));
}

// Called every frame
void APlayerShip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!RotateVelocity.IsZero())
		SetActorRotation(GetActorRotation() + RotateVelocity * DeltaTime);

	Velocity += Acceleration;

	
	if (!Velocity.IsZero())
	{
		SetActorLocation(Common::CheckEdge(GetActorLocation() + Velocity * DeltaTime));
		CheckVelocity();
	}

	if (bThrust)
		ThrustOn();	
}

void APlayerShip::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (!bHitCounted && !bHitObject)
		{
			bHitObject = true;
			bHitCounted = false;
			ActorHit = OtherActor;
		}
	}
}

void APlayerShip::OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		bHitObject = false;
		bHitCounted = true;
		ActorHit = NULL;
	}
}

// Functions for other classes.
void APlayerShip::Disable()
{
	ShipMeshComponent->SetCollisionProfileName("");
	ShipMeshComponent->bGenerateOverlapEvents = false;
}

void APlayerShip::SpawnShip()
{	
	// Create the mesh component
	ShipMeshComponent->SetCollisionProfileName("Player");
	ShipMeshComponent->bGenerateOverlapEvents = true;
	//ShipMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerShip::OnOverlap);
	//ShipMeshComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerShip::OnEndOverlap);
	RootComponent = ShipMeshComponent;
	bShipSpawned = true;
	SetActorRotation(FRotator(0, 90, 0));
	SetActorLocation(FVector(0, 0, 100));
}

void APlayerShip::ShipHit(uint16 points)
{
	Score += points;
	bHit = true;
}

//Input functions
void APlayerShip::RotateRight()
{
	RotateVelocity.Yaw = -RotateSpeed;
}

void APlayerShip::RotateLeft()
{
	RotateVelocity.Yaw = RotateSpeed;
}

void APlayerShip::StopRotation()
{
	RotateVelocity.Yaw = 0;
}

void APlayerShip::Thrust()
{
	bThrust = true;
}

void APlayerShip::StopThrust()
{
	Acceleration.Y = 0;
	Acceleration.X = 0;
	bThrust = false;
}

void APlayerShip::ThrustOn()
{
	FVector AngleInDeg = GetActorRotation().Euler();
	float ZAngleInRad = FMath::DegreesToRadians(AngleInDeg.Z);

	Acceleration.X = FMath::Cos(ZAngleInRad);
	Acceleration.Y = FMath::Sin(ZAngleInRad);
	Acceleration.Z = 0;
}

void APlayerShip::Hyperspace()
{
	Velocity = FVector(0, 0, 0);
	SetActorLocation(FVector(FMath::RandRange(-95, 95), FMath::RandRange(-50, 50), 100));
}

void APlayerShip::CheckVelocity()
{	
	if (Velocity.X > MoveSpeed)
		Velocity.X = MoveSpeed;
	
	if (Velocity.X < -MoveSpeed)
		Velocity.X = -MoveSpeed;

	if (Velocity.Y > MoveSpeed)
		Velocity.Y = MoveSpeed;

	if (Velocity.Y < -MoveSpeed)
		Velocity.Y = -MoveSpeed;	
}

