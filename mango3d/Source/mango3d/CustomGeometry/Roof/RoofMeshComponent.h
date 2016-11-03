// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "Util/CustomGeometryUtil.h"
#include "RoofMeshComponent.generated.h"


class RoomData;
/**
 * 
 */
UCLASS()
class MANGO3D_API URoofMeshComponent : public UProceduralMeshComponent
{
  GENERATED_UCLASS_BODY()
	
public:
  void InitWithRoomData(const RoomData* roomData);

private:
  ProceduralMeshData build_mesh_section(const RoomData* roomData);
	
	
};
