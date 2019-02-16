#include "AsteroidsUnreal.h"
#include "PlayerShipDisplay.h"


// Sets default values
APlayerShipDisplay::APlayerShipDisplay()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Load Mesh File.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Player/CorvetteShip.CorvetteShip"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));	
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	ShipMeshComponent->SetMobility(EComponentMobility::Movable);
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->RelativeScale3D = FVector(0.1f, 0.1f, 0.1f);
	SetActorRotation(FRotator(0, 90, 0));
}

// Called when the game starts or when spawned
void APlayerShipDisplay::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerShipDisplay::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

