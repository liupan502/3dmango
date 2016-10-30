// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Entity/CornerData.h"
#include "WallMeshComponent.h"

UWallMeshComponent::UWallMeshComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer) {
 
}

UWallMeshComponent::UWallMeshComponent() {
  //int a = 0;
  //ClearAllMeshSections();
  

}

void UWallMeshComponent::TestInit() {
  TArray<FVector> vertices;
  FVector vertex1 = FVector(0.0, 0.0, 0.0);
  vertices.Add(vertex1);
  FVector vertex2 = FVector(0, 100, 0);
  vertices.Add(vertex2);
  FVector vertex3 = FVector(100, 0, 0);
  vertices.Add(vertex3);

  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);

  TArray<FVector> normals;
  normals.Add(FVector(1, 0, 0));
  normals.Add(FVector(1, 0, 0));
  //normals.Add(FVector(1, 0, 0));

  TArray<FVector2D> uv0s;
  uv0s.Add(FVector2D(0, 0));
  uv0s.Add(FVector2D(0, 10));
  //uv0s.Add(FVector2D(10, 10));

  TArray<FColor> vertex_colors;
  vertex_colors.Add(FColor(255, 255, 255, 255));
  vertex_colors.Add(FColor(255, 255, 255, 255));
  //vertex_colors.Add(FColor(255, 255, 255, 255));

  TArray<FProcMeshTangent> tangents;
  tangents.Add(FProcMeshTangent(1, 1, 1));
  tangents.Add(FProcMeshTangent(1, 1, 1));
  //tangents.Add(FProcMeshTangent(1, 1, 1));
  //FProcMeshTangent
  CreateMeshSection(0, vertices, triangles, normals, uv0s, vertex_colors, tangents, false);
}

void UWallMeshComponent::CreateMeshSectionWithData(int sectionIndex, ProceduralMeshData& data) {
  CreateMeshSection(sectionIndex, data.vertices, data.triangles,
    data.normals, data.uv0s, data.vertex_colors,
    data.tangents, data.bool_value);
}

ProceduralMeshData UWallMeshComponent::build_wall_data_section1(const WallData* wallData) {
  ProceduralMeshData data;
  FVector start_position = wallData->StartCornerPosition();
  FVector start_top_position = start_position;
  start_top_position.Z = wall_height_;

  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector start_outside_top_position = start_outside_position;
  start_outside_top_position.Z = wall_height_;

  TArray<FVector> vertices;
  vertices.Add(start_position);
  vertices.Add(start_outside_position);
  vertices.Add(start_outside_top_position);
  vertices.Add(start_top_position);
  data.vertices = vertices;


  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);
  data.triangles = triangles;

  return data;
}

ProceduralMeshData UWallMeshComponent::build_wall_data_section2(const WallData* wallData) {
  ProceduralMeshData data;

  FVector start_position = wallData->StartCornerPosition();
  FVector start_top_position = start_position;
  start_top_position.Z = wall_height_;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;

  TArray<FVector> vertices;
  vertices.Add(start_inside_position);
  vertices.Add(start_position);
  vertices.Add(start_top_position);
  vertices.Add(start_inside_top_position);
  data.vertices = vertices;

  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);
  data.triangles = triangles;

  return data;
}

ProceduralMeshData UWallMeshComponent::build_wall_data_section3(const WallData* wallData) {
  ProceduralMeshData data;

  FVector end_position = wallData->EndCornerPosition();
  FVector end_top_position = end_position;
  end_top_position.Z = wall_height_;

  FVector end_outside_position = wallData->EndOutsidePosition();
  FVector end_outside_top_position = end_outside_position;
  end_outside_top_position.Z = wall_height_;

  TArray<FVector> vertices;
  vertices.Add(end_outside_position);
  vertices.Add(end_position);
  vertices.Add(end_top_position);
  vertices.Add(end_outside_top_position);
  data.vertices = vertices;


  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);
  data.triangles = triangles;

  return data;
}

ProceduralMeshData UWallMeshComponent::build_wall_data_section4(const WallData* wallData) {
  ProceduralMeshData data;

  FVector end_position = wallData->EndCornerPosition();
  FVector end_top_position = end_position;
  end_top_position.Z = wall_height_;

  FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;

  TArray<FVector> vertices;
  vertices.Add(end_position);
  vertices.Add(end_inside_position);
  vertices.Add(end_inside_top_position);
  vertices.Add(end_top_position);
  data.vertices = vertices;


  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);
  data.triangles = triangles;

  return data;
}

ProceduralMeshData UWallMeshComponent::build_wall_data_section5(const WallData* wallData) {
  ProceduralMeshData data;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;

  FVector start_position = wallData->StartCornerPosition();
  FVector start_top_position = start_position;
  start_top_position.Z = wall_height_;

  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector start_outside_top_position = start_outside_position;
  start_outside_top_position.Z = wall_height_;

  FVector end_outside_position = wallData->EndOutsidePosition();
  FVector end_outside_top_position = end_outside_position;
  end_outside_top_position.Z = wall_height_;

  FVector end_position = wallData->EndCornerPosition();
  FVector end_top_position = end_position;
  end_top_position.Z = wall_height_;

  FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;

  TArray<FVector> vertices;
  vertices.Add(start_inside_top_position);
  vertices.Add(start_top_position);
  vertices.Add(start_outside_top_position);
  vertices.Add(end_outside_top_position);
  vertices.Add(end_top_position);
  vertices.Add(end_inside_top_position);
  data.vertices = vertices;

  TArray<FVector> normals;
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  data.normals = normals;

  TArray<int32> triangles;
  /*triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);
  
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);

  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(4);

  triangles.Add(0);
  triangles.Add(4);
  triangles.Add(5);*/

  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(1);

  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(2);

  triangles.Add(0);
  triangles.Add(4);
  triangles.Add(3);

  triangles.Add(0);
  triangles.Add(5);
  triangles.Add(4);

  data.triangles = triangles;
  

  return data;
}

ProceduralMeshData UWallMeshComponent::build_wall_data_section6(const WallData* wallData) {
  ProceduralMeshData data;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_position = wallData->StartCornerPosition();
  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector end_outside_position = wallData->EndOutsidePosition();  
  FVector end_position = wallData->EndCornerPosition();
  FVector end_inside_position = wallData->EndInsidePosition();
  

  TArray<FVector> vertices;
  vertices.Add(start_inside_position);
  vertices.Add(start_position);
  vertices.Add(start_outside_position);
  vertices.Add(end_outside_position);
  vertices.Add(end_position);
  vertices.Add(end_inside_position);
  data.vertices = vertices;

  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);

  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);

  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(4);

  triangles.Add(0);
  triangles.Add(4);
  triangles.Add(5);

  data.triangles = triangles;

  return data;
}

ProceduralMeshData UWallMeshComponent::build_wall_data_section7(const WallData* wallData, TArray<OpeningData*>& openings) {
  ProceduralMeshData data;

  FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;

  TArray<FVector> vertices;
  vertices.Add(end_inside_position);
  vertices.Add(start_inside_position);
  vertices.Add(start_inside_top_position);
  vertices.Add(end_inside_top_position);
  data.vertices = vertices;

  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);

  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);

  data.triangles = triangles;


  return data;
}

ProceduralMeshData UWallMeshComponent::build_wall_data_section8(const WallData* wallData, TArray<OpeningData*>& openings) {
  ProceduralMeshData data;

  FVector end_outside_position = wallData->EndOutsidePosition();
  FVector end_outside_top_position = end_outside_position;
  end_outside_top_position.Z = wall_height_;

  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector start_outside_top_position = start_outside_position;
  start_outside_top_position.Z = wall_height_;

  TArray<FVector> vertices;
  vertices.Add(start_outside_position);
  vertices.Add(end_outside_position);
  vertices.Add(end_outside_top_position);
  vertices.Add(start_outside_top_position);
  data.vertices = vertices;

  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1);
  triangles.Add(2);

  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);

  data.triangles = triangles;

  return data;
}

TArray<FVector> split_face(TArray<FVector>& face, TArray<OpeningData*>& openings) {
  TArray<FVector> face_points;
  if (openings.Num() == 0) {
    face_points = face;
    return face_points;
  }
  return face_points;
}

TArray<ProceduralMeshData> UWallMeshComponent::build_opening_sections(const WallData* wallData, TArray<OpeningData*>& openings) {
  TArray<ProceduralMeshData> mesh_datas;
  return mesh_datas;
}

void UWallMeshComponent::InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings) {
  
  ClearAllMeshSections();
  
  ProceduralMeshData mesh_data0 =  build_wall_data_section1(wallData);
  //CreateMeshSectionWithData(0, mesh_data0);

  ProceduralMeshData mesh_data1 = build_wall_data_section2(wallData);
  //CreateMeshSectionWithData(1, mesh_data1);

  ProceduralMeshData mesh_data2 = build_wall_data_section3(wallData);
  //CreateMeshSectionWithData(2, mesh_data2);

  ProceduralMeshData mesh_data3 = build_wall_data_section4(wallData);
  //CreateMeshSectionWithData(3, mesh_data3);

  ProceduralMeshData mesh_data4 = build_wall_data_section5(wallData);
  CreateMeshSectionWithData(4, mesh_data4);

  ProceduralMeshData mesh_data5 = build_wall_data_section6(wallData);
  //CreateMeshSectionWithData(5, mesh_data5);

  ProceduralMeshData mesh_data6 = build_wall_data_section7(wallData, openings);
  //CreateMeshSectionWithData(6, mesh_data6);

  ProceduralMeshData mesh_data7 = build_wall_data_section8(wallData, openings);
  //CreateMeshSectionWithData(7, mesh_data7);
}

