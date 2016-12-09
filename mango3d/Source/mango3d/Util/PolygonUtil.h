#pragma once
#include "mango3d.h"


bool IsClockwisePolygon(TArray<FVector2D> polygon);

bool IsConvexVertex(FVector2D preVertex, FVector2D vertex, FVector2D nextVertex);

TArray<FVector2D> Triangulation(TArray<FVector2D> polygon);

bool IsPointInPolygon(const FVector2D point, const TArray<FVector2D>& polygon);

int IsPolygonInPolygon(const TArray<FVector2D>& polygon1, const TArray<FVector2D>& polygon2);

TArray<FVector2D> GetIntersectionOfConvexPolygon(const TArray<FVector2D>& polygon1, const TArray<FVector2D>& polygon2);

TArray<FVector2D> MANGO3D_API GetBoundingRect(const TArray<FVector2D>& polygon);

