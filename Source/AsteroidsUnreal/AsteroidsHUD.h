#pragma once
#include "GameFramework/HUD.h"
#include "AsteroidsHUD.generated.h"

UCLASS()
class ASTEROIDSUNREAL_API AAsteroidsHUD : public AHUD
{
	GENERATED_BODY()

private:

public:
	AAsteroidsHUD(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UFont* HUDFont;

	// Called when screen draws
	virtual void DrawHUD() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	uint32 Score;

	bool bGameOver;

	FVector2D ScreenDimensions;
	FString ScoreString;
};
