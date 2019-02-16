#include "AsteroidsUnreal.h"
#include "PlayerClearToSpawn.h"


// Sets default values
APlayerClearToSpawn::APlayerClearToSpawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Player/ClearSphere.ClearSphere"));  //StaticMesh'/Game/Player/ClearSphere.ClearSphere'
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetStaticMesh(ShipMesh.Object);
	//MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerClearToSpawn::OnOverlap);
	//MeshComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerClearToSpawn::OnEndOverlap);
	MeshComponent->bVisible = false;
	MeshComponent->SetCollisionProfileName("Player");
	MeshComponent->bGenerateOverlapEvents = true;
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void APlayerClearToSpawn::BeginPlay()
{
	NumberOfHits = 0;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ClearTimerExpired, this, &APlayerClearToSpawn::Clear, 1);
}

// Called every frame
void APlayerClearToSpawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void APlayerClearToSpawn::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		bIsClear = false;
		ActorHit = OtherActor;
		NumberOfHits++;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ClearTimerExpired, this, &APlayerClearToSpawn::Clear, 2);
	}
}

void APlayerClearToSpawn::OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ClearTimerExpired, this, &APlayerClearToSpawn::Clear, 0.15f);
		NumberOfHits--;
		ActorHit = OtherActor;
	}
}

void APlayerClearToSpawn::Clear()
{
	if (NumberOfHits == 0)
		bIsClear = true;
}

void APlayerClearToSpawn::Disable()
{
	MeshComponent->SetCollisionProfileName("");
	MeshComponent->bGenerateOverlapEvents = false;
}