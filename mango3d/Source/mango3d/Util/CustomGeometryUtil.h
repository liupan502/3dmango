#pragma once
#include "mango3d.h"

#include "ProceduralMeshComponent.h"
#include "Engine/BrushBuilder.h"
#include "GameFramework/Volume.h"
class RoomData;
class OpeningData;
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

  void Append(const ProceduralMeshData& data) {
    int base_vertex_index = vertices.Num();
    for (int i = 0; i < data.triangles.Num(); i++) {
      triangles.Add(data.triangles[i] + base_vertex_index);
    }
    vertices.Append(data.vertices);    
    normals.Append(data.normals);
    uv0s.Append(data.uv0s);
    vertex_colors.Append(data.vertex_colors);
    tangents.Append(data.tangents);
    bool_value = bool_value&&data.bool_value;
  }
};

TArray<FVector2D> BuildRoomMesh(const RoomData* roomData);

TArray<FVector2D> BuildRoomMesh(const RoomData* roomData, float texWidth, float texLength);

TArray<FVector2D> GetRoomDataCornerPositions(const RoomData* roomData);

void CreateMeshSectionWithData(UProceduralMeshComponent* umc, int sectionIndex, ProceduralMeshData& data);

int SampleComputeUVTileNum(const TArray<FVector2D>& polygon, float texWidth, float texHeight);

TArray<FVector2D> GetUVRect(const TArray<FVector2D>& polygon,float texWidth,float texHeight);

FVector2D ComputeUV(const TArray<FVector2D>& uvRect, FVector2D vertex);

void build_wall_vertical_face(TArray<FVector> vectors, TArray<OpeningData*>& openings, 
  ProceduralMeshData& data, float texWidth = -1, float texHeight = -1);

FMatrix compute_wall_matrix(FVector start_position, FVector end_position);

TArray<FVector2D> split_face(TArray<FVector2D>& face, TArray<FVector2D>& openings);

TArray<FVector> compute_opening_vertex(FVector start_point, FVector end_point, 
  OpeningData* openingData, const FMatrix& mat);

UStaticMesh* GetStaticMesh(UProceduralMeshComponent* com,FString meshName);

void MANGO3D_API CreateBrushForVolumeActor(AVolume* NewActor, UBrushBuilder* BrushBuilder);
