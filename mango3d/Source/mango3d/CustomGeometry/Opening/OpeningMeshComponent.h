// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "Entity/OpeningData.h"
#include "Entity/WallData.h"
#include "Util/CustomGeometryUtil.h"
#include "OpeningMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class MANGO3D_API UOpeningMeshComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()
	
	
public:
  void InitWithOpeningData( OpeningData* openingData,  WallData* wallData);

protected:
  virtual ProceduralMeshData build_mesh_section( OpeningData* openingData,  WallData* wallData);
	
};
