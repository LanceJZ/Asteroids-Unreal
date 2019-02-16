#include "AsteroidsUnreal.h"
#include "LargeUFO.h"


// Sets default values
ALargeUFO::ALargeUFO(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Find static mesh.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> UFOMesh(TEXT("/Game/UFOs/LargeUFO.LargeUFO"));
	// Create the mesh component
	UFOMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UFOMesh"));
	UFOMeshComponent->SetStaticMesh(UFOMesh.Object);
	UFOMeshComponent->SetMobility(EComponentMobility::Movable);
	UFOMeshComponent->SetCollisionProfileName("UFO");
	UFOMeshComponent->bGenerateOverlapEvents = true;
	//UFOMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ALargeUFO::OnOverlap);
	//UFOMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ALargeUFO::OnEndOverlap);
	RootComponent = UFOMeshComponent;
	UFOMeshComponent->RelativeScale3D = FVector(1.0f, 1.0f, 1.0f);
	bHitObject = false;
	bHitOtherSide = false;
	Velocity.ZeroVector;
}

// Called when the game starts or when spawned
void ALargeUFO::BeginPlay()
{
	Super::BeginPlay();

	AActor::SetActorLabel("LargeUFO");

	pShot = NULL;

	float RVP = 150.6;

	RotateVelocity = FRotator(5, 0, 0);

	Score = 200;

	float Start;

	if (FMath::RandRange(0, 10) > 5)
	{
		bFromRightSide = true;
		Start = 105;
	}
	else
	{
		bFromRightSide = false;
		Start = -105;
	}

	XRotation = 0;
	VectorChangeRate = 8;
	ERotation.ZeroVector;
	SetActorLocation(FVector(Start, FMath::RandRange(-50, 50), 100));
	ChangeVector();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireTimerExpired, this, &ALargeUFO::FireShot, FMath::RandRange(1, 2));
}

// Called every frame
void ALargeUFO::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	SetActorLocation(Common::CheckEdge(GetActorLocation() + Velocity * DeltaTime));

	ERotation.Y = 600.0f *DeltaTime;
	ERotation.X = 0;
	ERotation.Z = 0;
	
	FQuat fixedRotation;
	FTransform TheTransform = GetTransform();
	fixedRotation.MakeFromEuler(ERotation);
	TheTransform.ConcatenateRotation(fixedRotation);
	SetActorTransform(TheTransform);

	if (GetActorLocation().X > 100 && !bFromRightSide)
		bHitOtherSide = true;

	if (GetActorLocation().X < -100 && bFromRightSide)
		bHitOtherSide = true;
}

void ALargeUFO::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		bHitObject = true;
		ActorHit = OtherActor;
	}
}

void ALargeUFO::OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		bHitObject = false;
		ActorHit = NULL;
	}
}

void ALargeUFO::ChangeVector()
{
	float MoveSpeed = 12.5;

	if (bFromRightSide)
		Velocity.X = -MoveSpeed;
	else
		Velocity.X = MoveSpeed;

	uint8 RA = FMath::RandRange(0, 15);

	if (RA < 5)
	{
		Velocity.Y = MoveSpeed;
	}
	else if (RA > 5 && RA < 10)
	{
		Velocity.Y = 0;
	}
	else
	{
		Velocity.Y = -MoveSpeed;
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_VectorTimerExpired, this, &ALargeUFO::ChangeVector, FMath::RandRange(3.0, VectorChangeRate));
}

void ALargeUFO::FireShot()
{
	UWorld* const World = GetWorld();
	FVector FireDirection;
	FRotator DirectionOfShot;

	DirectionOfShot.Yaw = FMath::RandRange(0, 360);

	FVector AngleInDeg = DirectionOfShot.Euler();
	float ZAngleInRad = FMath::DegreesToRadians(AngleInDeg.Z);

	FireDirection.X = FMath::Cos(ZAngleInRad) * 2.5f;
	FireDirection.Y = FMath::Sin(ZAngleInRad) * 2.5f;
	FireDirection.Z = 0;

	pShot = World->SpawnActor<AShot>(GetActorLocation() + FireDirection, DirectionOfShot - FRotator(0, 90, 0));
	World->GetTimerManager().SetTimer(TimerHandle_FireTimerExpired, this, &ALargeUFO::FireShot, FMath::RandRange(1, 2));
}