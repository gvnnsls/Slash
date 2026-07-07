#pragma once

#define DRAW_LINE(LineStart, LineEnd) if(GetWorld()) DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Cyan, true)
#define DRAW_LINE_SingleFrame(LineStart, LineEnd) if(GetWorld()) DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Cyan)
#define DRAW_SPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 20, 24, FColor::Yellow, true)
#define DRAW_SPHERE_SingleFrame(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 20, 24, FColor::Yellow)

#define DRAW_DOT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 20, FColor::Cyan, true);
#define DRAW_DOT_SingleFrame(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 20, FColor::Cyan)

#define DRAW_VECTOR(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Cyan, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 20, FColor::Cyan, true); \
	}
#define DRAW_VECTOR_SingleFrame(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Cyan); \
		DrawDebugPoint(GetWorld(), EndLocation, 20, FColor::Cyan); \
	}