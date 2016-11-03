#pragma once
#include "mango3d.h"
#include "ProceduralMeshComponent.h"
class RoomData;
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

TArray<FVector2D> BuildRoomMesh(const RoomData* roomData);

void CreateMeshSectionWithData(UProceduralMeshComponent* umc, int sectionIndex, ProceduralMeshData& data);
