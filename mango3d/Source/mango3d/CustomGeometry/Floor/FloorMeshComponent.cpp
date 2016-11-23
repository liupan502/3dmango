// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "FloorMeshComponent.h"
#include "Util/CustomGeometryUtil.h"
#include "Util/PolygonUtil.h"
#include "Entity/RoomData.h"


UFloorMeshComponent::UFloorMeshComponent(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) {

}

void UFloorMeshComponent::InitWithRoomData(const RoomData* roomData) {
  if (roomData == NULL) {
    return;
  }

  ClearAllMeshSections();
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/Model/diban/Mat/floor03.floor03'"));


  ProceduralMeshData mesh_data0 = build_mesh_section(roomData);
  CreateMeshSectionWithData(this, 0, mesh_data0);
  SetMaterial(0, mat);
}

ProceduralMeshData UFloorMeshComponent::build_mesh_section(const RoomData* roomData) {
  ProceduralMeshData data;
  TArray<FVector2D> vertices_rect = BuildRoomMesh(roomData,50,50);
  TArray<FVector2D> vertices_tri = BuildRoomMesh(roomData);

  TArray<FVector2D> corner_vertices = roomData->GetCornerPositions();
  TArray<FVector> vertices;
  TArray<FVector2D> uv0s;
  TArray<FVector> normals;
  TArray<int32> triangles;
  for (int i = 0; i < vertices_rect.Num() / 4; i++) {
    TArray<FVector2D> rect;
    rect.Add(vertices_rect[4 * i]);
    rect.Add(vertices_rect[4 * i+1]);
    rect.Add(vertices_rect[4 * i+2]);
    rect.Add(vertices_rect[4 * i+3]);

    int status = IsPolygonInPolygon(rect, corner_vertices);
    if (status == 1) {
      int vertices_num = vertices.Num();
      vertices.Add(FVector(rect[0], 0.0));
      vertices.Add(FVector(rect[1], 0.0));
      vertices.Add(FVector(rect[2], 0.0));
      vertices.Add(FVector(rect[3], 0.0));

      uv0s.Add(FVector2D(0.0, 0.0));
      uv0s.Add(FVector2D(1.0, 0.0));
      uv0s.Add(FVector2D(1.0, 1.0));
      uv0s.Add(FVector2D(0.0, 1.0));

      
      triangles.Add(3+ vertices_num);
      triangles.Add(1+ vertices_num);
      triangles.Add(0+ vertices_num);

      triangles.Add(3+ vertices_num);
      triangles.Add(2+ vertices_num);
      triangles.Add(1+ vertices_num);
      
    }
    else if (status == 0) {

    }
  }

  for (int i = 0; i < vertices.Num(); i++) {
    normals.Add(FVector(0.0, 0.0, 1.0));
  }
  data.vertices = vertices;
  data.uv0s = uv0s;
  data.triangles = triangles;
  data.normals = normals;
  

  /*TArray<FVector> vertices;
  TArray<int> triangles;
  FVector normal(0, 0, 1);
  TArray<FVector> normals;
  for (int i = 0; i < vertices_2d.Num(); i++) {
    vertices.Add(FVector(vertices_2d[i].X, vertices_2d[i].Y, 0));
    triangles.Add(i);
    normals.Add(normal);
  }
  for (int i = 0; i < triangles.Num() / 3; i++) {
    int tmp = triangles[3 * i + 1];
    triangles[3 * i + 1] = triangles[3 * i + 2];
    triangles[3 * i + 2] = tmp;
  }
  data.vertices = vertices;
  data.triangles = triangles;
  data.normals = normals;*/

  return data;
}




