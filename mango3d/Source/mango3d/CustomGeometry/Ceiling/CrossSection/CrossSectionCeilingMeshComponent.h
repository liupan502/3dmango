// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "Entity/CeilingData.h"
#include "Entity/RoomData.h"
#include "Util/CustomGeometryUtil.h"
#include "CrossSectionCeilingMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class MANGO3D_API UCrossSectionCeilingMeshComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()
	
	
public:
  void InitWithCrossSectionCeilingData(CrossSectionCeilingData* data,RoomData* roomData);

protected:
  ProceduralMeshData build_mesh_section(CrossSectionCeilingData* ceilingData,RoomData* roomData);
	
  ProceduralMeshData build_line_unit_mesh_section(LineCeilingUnit* unit, 
     TArray<FVector> points,  bool isClockwise,FVector2D uvOffset,float uvScale);
};
