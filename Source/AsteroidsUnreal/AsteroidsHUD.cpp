#include "AsteroidsUnreal.h"
#include "AsteroidsHUD.h"
#include "GameSpawner.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"

AGameSpawner* Spawner;

AAsteroidsHUD::AAsteroidsHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;
}

void AAsteroidsHUD::BeginPlay()
{
	Spawner = Cast<AGameSpawner>(GetOwningPawn());
}

void AAsteroidsHUD::DrawHUD()
{
	Super::DrawHUD();

	ScoreString = FString::FormatAsNumber(Spawner->pPlayerShot->Score);
	ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	//FVector2D ScoreSize;
	//GetTextSize(ScoreString, ScoreSize.X, ScoreSize.Y, HUDFont);
	DrawText(ScoreString, FColor::White, 50, 50, HUDFont);
	
	if (Spawner->bGameOver)
	{
		FVector2D GameOverSize;
		HUDFont->ScalingFactor = 10;
		GetTextSize(TEXT("Game Over"), GameOverSize.X, GameOverSize.Y, HUDFont);
		DrawText(TEXT("Game Over"), FColor::White, (ScreenDimensions.X - GameOverSize.X) / 2.0f, (ScreenDimensions.Y - GameOverSize.Y) / 2.0f, HUDFont);
	}
}