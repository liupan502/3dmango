// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "RoofMeshComponent.h"
#include "Util/CustomGeometryUtil.h"
#include "Entity/RoomData.h"
URoofMeshComponent::URoofMeshComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer) {

}

void URoofMeshComponent::InitWithRoomData(const RoomData* roomData) {
  if (roomData == NULL) {
    return;
  }

  ClearAllMeshSections();
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/WallDefaultMat.WallDefaultMat'"));


  ProceduralMeshData mesh_data0 = build_mesh_section(roomData);
  CreateMeshSectionWithData(this, 0, mesh_data0);
  SetMaterial(0, mat);
}

ProceduralMeshData URoofMeshComponent::build_mesh_section(const RoomData* roomData) {
  ProceduralMeshData data;
  TArray<FVector2D> vertices_2d = BuildRoomMesh(roomData);
  TArray<FVector> vertices;
  //TArray<FVector> vertices1;
  TArray<int> triangles;

  FVector normal(0, 0, -1);
  TArray<FVector> normals;
  
  data.normals = normals;
  for (int i = 0; i < vertices_2d.Num(); i++) {
    vertices.Add(FVector(vertices_2d[i].X, vertices_2d[i].Y, 280));
    triangles.Add(i);
    normals.Add(normal);
  }
  for (int i = 0; i < vertices_2d.Num(); i++) {
    vertices.Add(FVector(vertices_2d[i].X, vertices_2d[i].Y, 300));
    triangles.Add(i+ vertices_2d.Num());
    normals.Add(normal);
  }
  
  TArray<FVector2D> corner_positions = GetRoomDataCornerPositions(roomData);
  for (int i = 0; i < corner_positions.Num(); i++) {
    int j = (i + 1) % corner_positions.Num();
    FVector position1 = FVector(corner_positions[i],280);
    FVector position2 = FVector(corner_positions[j],280);
    FVector position1_up = FVector(corner_positions[i], 300);
    FVector position2_up = FVector(corner_positions[j], 300);
    int vertex_base_index = vertices.Num();
    vertices.Add(position1);
    vertices.Add(position2);
    vertices.Add(position2_up);
    vertices.Add(position1_up);

    FVector tmp = position2 - position1;
    FVector tmp_normal(-tmp.Y, tmp.X, 0);
    normals.Add(tmp_normal);
    normals.Add(tmp_normal);
    normals.Add(tmp_normal);
    normals.Add(tmp_normal);

    triangles.Add(vertex_base_index);
    triangles.Add(vertex_base_index+1);
    triangles.Add(vertex_base_index+2);

  
    triangles.Add(vertex_base_index );
    triangles.Add(vertex_base_index + 2);
    triangles.Add(vertex_base_index + 3);
  }
  data.vertices = vertices;
  data.triangles = triangles; 
  data.normals = normals;

  return data;
}


