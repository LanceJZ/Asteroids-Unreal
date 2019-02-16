#include "AsteroidsUnreal.h"
#include "Common.h"

Common::Common()
{
}

FVector Common::CheckEdge(FVector position)
{
	FVector FixedPosition = position;

	if (position.X > 105)
		FixedPosition.X = - 105;

	if (position.X < -105)
		FixedPosition.X = 105;

	if (position.Y > 60)
		FixedPosition.Y = -60;

	if (position.Y < -60)
		FixedPosition.Y = 60;

	return FixedPosition;
}
