// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "Entity/DesignData.h"
#include "Util/CustomGeometryUtil.h"
#include "OutsideWallMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class MANGO3D_API UOutsideWallMeshComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()
	
public:
  void InitWithDesignData( DesignData* designData);
	
protected:
  ProceduralMeshData build_mesh_section(DesignData* designData);
};
