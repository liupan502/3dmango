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
  //UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/WallDefaultMat.WallDefaultMat'"));
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/Model/diban/Mat/floor03.floor03'"));
  UMaterialInstanceDynamic* mat_instance = CreateAndSetMaterialInstanceDynamicFromMaterial(0, mat);
  TArray<FVector2D> corner_positions = GetRoomDataCornerPositions(roomData);
  float texWidth = 75, texHeight = 75;
  int uv_tile_num = SampleComputeUVTileNum(corner_positions, texWidth, texHeight);
  mat_instance->SetScalarParameterValue("TileScale", uv_tile_num);
  ProceduralMeshData mesh_data0 = build_mesh_section(roomData);

  //ProceduralMeshData mesh_data0 = build_mesh_section(roomData);
  CreateMeshSectionWithData(this, 0, mesh_data0);
  //SetMaterial(0, mat);
}

ProceduralMeshData URoofMeshComponent::build_mesh_section(const RoomData* roomData) {
  ProceduralMeshData data;
  float texWidth = 75, texHeight = 75;
  TArray<FVector2D> vertices_2d = BuildRoomMesh(roomData);
  TArray<FVector> vertices;
  
  TArray<int> triangles;

  FVector normal(0, 0, -1);
  TArray<FVector> normals;
  TArray<FVector2D> corner_positions = GetRoomDataCornerPositions(roomData);
  TArray<FVector2D> uv_rect = GetUVRect(corner_positions, texWidth, texHeight);
  TArray<FVector2D> uv0s;
  
  for (int i = 0; i < vertices_2d.Num(); i++) {
    FVector2D uv = ComputeUV(uv_rect, vertices_2d[i]);
    uv0s.Add(uv);
    vertices.Add(FVector(vertices_2d[i].X, vertices_2d[i].Y, 280));
    triangles.Add(i);
    normals.Add(normal);
  }
  /*for (int i = 0; i < vertices_2d.Num(); i++) {
    vertices.Add(FVector(vertices_2d[i].X, vertices_2d[i].Y, 300));
    triangles.Add(i+ vertices_2d.Num());
    normals.Add(normal);
  }*/
  
  /*TArray<FVector2D> corner_positions = GetRoomDataCornerPositions(roomData);
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
  }*/
  data.vertices = vertices;
  data.triangles = triangles; 
  data.normals = normals;
  data.uv0s = uv0s;

  return data;
}


