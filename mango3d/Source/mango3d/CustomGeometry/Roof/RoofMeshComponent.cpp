// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "RoofMeshComponent.h"
#include "Util/CustomGeometryUtil.h"
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
  TArray<int> triangles;
  for (int i = 0; i < vertices_2d.Num(); i++) {
    vertices.Add(FVector(vertices_2d[i].X, vertices_2d[i].Y, 280));
    triangles.Add(i);
  }
  data.vertices = vertices;
  data.triangles = triangles; 

  return data;
}


