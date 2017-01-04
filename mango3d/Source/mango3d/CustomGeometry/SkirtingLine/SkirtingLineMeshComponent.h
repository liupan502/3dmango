// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "Util/CustomGeometryUtil.h"
#include "SkirtingLineMeshComponent.generated.h"

class WallData;
class OpeningData;
class RoomData;
/**
 * 
 */
UCLASS()
class MANGO3D_API USkirtingLineMeshComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()
	
public:
  void InitWithWallData(WallData* wallData, TArray<OpeningData*>& openings,RoomData* roomData);
protected:
  const int skirting_line_height_ = 12;
  const int skirting_line_width_ = 3;
  ProceduralMeshData build_mesh_section(WallData* wallData, TArray<OpeningData*>& openings, RoomData* roomData);
	
};
