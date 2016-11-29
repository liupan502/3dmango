// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "OpeningMeshComponent.h"


void UOpeningMeshComponent::InitWithOpeningData( OpeningData* openingData,   WallData* wallData) {
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/Model/diban/Mat/floor03.floor03'"));
  UMaterialInstanceDynamic* mat_instance = CreateAndSetMaterialInstanceDynamicFromMaterial(0, mat);
  ProceduralMeshData mesh_data0 = build_mesh_section(openingData,wallData);
  CreateMeshSectionWithData(this, 0, mesh_data0);
}

ProceduralMeshData UOpeningMeshComponent::build_mesh_section( OpeningData* openingData,  WallData* wallData) {
  ProceduralMeshData data;
  FVector start_inside_position = wallData->StartInsidePosition();
  FVector end_inside_position = wallData->EndInsidePosition();
  FMatrix mat = compute_wall_matrix(start_inside_position, end_inside_position);
  FMatrix inverse_mat = mat.Inverse();
  TArray<FVector> insdie_opening_vertices = compute_opening_vertex(start_inside_position,
    end_inside_position, openingData, inverse_mat);


  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector end_outside_position = wallData->EndOutsidePosition();
  TArray<FVector> outsdie_opening_vertices = compute_opening_vertex(start_outside_position,
    end_outside_position, openingData, inverse_mat);
  TArray<FVector> vertices = insdie_opening_vertices;
  vertices.Append(outsdie_opening_vertices);
  data.vertices = vertices;

  TArray<int32> triangles;

  for (int i = 0; i < 4; i++) {

    triangles.Add(i);
    triangles.Add(i + 4);
    triangles.Add((i + 1) % 4);
    triangles.Add((i + 1) % 4);
    triangles.Add(i + 4);
    triangles.Add((i + 1) % 4 + 4);
  }

  data.triangles = triangles;

  return data;
}

