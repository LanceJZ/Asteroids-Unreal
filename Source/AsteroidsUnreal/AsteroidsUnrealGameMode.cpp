#include "AsteroidsUnreal.h"
#include "AsteroidsUnrealGameMode.h"
#include "AsteroidsHUD.h"
#include "GameSpawner.h"

AAsteroidsUnrealGameMode::AAsteroidsUnrealGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = AGameSpawner::StaticClass();
	HUDClass = AAsteroidsHUD::StaticClass();
}
