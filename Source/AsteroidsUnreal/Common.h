#pragma once
#define M_PI 3.14159265358979323846 // Pi

class ASTEROIDSUNREAL_API Common
{
public:
	Common();

	static FVector CheckEdge(FVector position);

	FVector Velocity;
	FRotator RotateVelocity;
	float Score;
	AActor* ActorHit;
	bool bHitObject;
	bool bHitCounted;
};
