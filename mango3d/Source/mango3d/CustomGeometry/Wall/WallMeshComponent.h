// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Entity/WallData.h"
#include "Entity/OpeningData.h"
#include "ProceduralMeshComponent.h"
#include "WallMeshComponent.generated.h"


struct ProceduralMeshData {
  TArray<FVector> vertices;
  TArray<int32> triangles;
  TArray<FVector> normals; 
  TArray<FVector2D> uv0s;
  TArray<FColor> vertex_colors;
  TArray<FProcMeshTangent> tangents;
  bool bool_value;

  ProceduralMeshData() {
    bool_value = false;
  }
};


/**
 * 
 */
UCLASS(hidecategories = (Object, LOD, Physics, Collision), editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class MANGO3D_API UWallMeshComponent : public UProceduralMeshComponent
{
  GENERATED_UCLASS_BODY()
public:
  UWallMeshComponent();
  void TestInit();
  virtual void InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings);

private:

  const float wall_height_ = 280.0f;

  void CreateMeshSectionWithData(int sectionIndex,ProceduralMeshData& data);

  // start corner outside face
  ProceduralMeshData build_wall_data_section1(const WallData* wallData);

  // start corner inside face
  ProceduralMeshData build_wall_data_section2(const WallData* wallData);

  // end corner outside face 
  ProceduralMeshData build_wall_data_section3(const WallData* wallData);

  // end corner inside face
  ProceduralMeshData build_wall_data_section4(const WallData* wallData);

  // top face 
  ProceduralMeshData build_wall_data_section5(const WallData* wallData);

  // bottom face
  ProceduralMeshData build_wall_data_section6(const WallData* wallData);

  // inside face
  ProceduralMeshData build_wall_data_section7(const WallData* wallData, TArray<OpeningData*>& openings);

  // outside face
  ProceduralMeshData build_wall_data_section8(const WallData* wallData, TArray<OpeningData*>& openings);
	

  TArray<ProceduralMeshData> build_opening_sections(const WallData* wallData, TArray<OpeningData*>& openings);


  /*
  face order: 
  
  */
  TArray<FVector> split_face(TArray<FVector>& face, TArray<OpeningData*>& openings);
};
