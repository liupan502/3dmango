#pragma once
#include "mango3d.h"


bool IsClockwisePolygon(TArray<FVector2D> polygon);

bool IsConvexVertex(FVector2D preVertex, FVector2D vertex, FVector2D nextVertex);

TArray<FVector2D> Triangulation(TArray<FVector2D> polygon);

bool IsPointInPolygon(FVector2D point, const TArray<FVector2D> polygon);