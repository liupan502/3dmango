// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Entity/CornerData.h"
#include "WallMeshComponent.h"
#include "Util/PolygonUtil.h"
#include "Util/CustomGeometryUtil.h"


UWallMeshComponent::UWallMeshComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer) {
  int a = 0;
  //TestInit();
}

UWallMeshComponent::UWallMeshComponent() {
  //int a = 0;
  //ClearAllMeshSections();
  int a = 0;
  //TestInit();
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

/*void UWallMeshComponent::CreateMeshSectionWithData(int sectionIndex, ProceduralMeshData& data) {
  CreateMeshSection(sectionIndex, data.vertices, data.triangles,
    data.normals, data.uv0s, data.vertex_colors,
    data.tangents, data.bool_value);
}*/


// 起点外侧面网格构建
ProceduralMeshData UWallMeshComponent::build_wall_data_section1(const WallData* wallData) {
  ProceduralMeshData data;
  FVector start_position = wallData->StartCornerPosition();
  FVector start_top_position = start_position;
  start_top_position.Z = wall_height_;



  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector start_outside_top_position = start_outside_position;
  start_outside_top_position.Z = wall_height_;

  FVector end_outside_position = wallData->EndOutsidePosition();
  FVector tmp = start_outside_position - start_position;
  FVector normal(-tmp.Y, tmp.X, 0);
  TArray<FVector> normals;
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  data.normals = normals;


  TArray<FVector> vertices;
  vertices.Add(start_position);
  vertices.Add(start_outside_position);
  vertices.Add(start_outside_top_position);
  vertices.Add(start_top_position);
  data.vertices = vertices;


  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(1);
  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(2);
  data.triangles = triangles;

  return data;
}

// 起始点内侧面网格构建
ProceduralMeshData UWallMeshComponent::build_wall_data_section2(const WallData* wallData) {
  ProceduralMeshData data;

  FVector start_position = wallData->StartCornerPosition();
  FVector start_top_position = start_position;
  start_top_position.Z = wall_height_;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;

  FVector end_inside_position = wallData->EndInsidePosition();
  FVector tmp = start_position - start_inside_position;
  FVector normal(-tmp.Y, tmp.X, 0);
  TArray<FVector> normals;
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  data.normals = normals;

  TArray<FVector> vertices;
  vertices.Add(start_inside_position);
  vertices.Add(start_position);
  vertices.Add(start_top_position);
  vertices.Add(start_inside_top_position);
  data.vertices = vertices;

  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(1);
  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(2);
  data.triangles = triangles;

  return data;
}

// 终止点外侧面网格构建
ProceduralMeshData UWallMeshComponent::build_wall_data_section3(const WallData* wallData) {
  ProceduralMeshData data;

  FVector end_position = wallData->EndCornerPosition();
  FVector end_top_position = end_position;
  end_top_position.Z = wall_height_;

  FVector end_outside_position = wallData->EndOutsidePosition();
  FVector end_outside_top_position = end_outside_position;
  end_outside_top_position.Z = wall_height_;

  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector tmp = end_position - end_outside_top_position;
  FVector normal(-tmp.Y, tmp.X, 0);
  TArray<FVector> normals;
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  data.normals = normals;

  TArray<FVector> vertices;
  vertices.Add(end_outside_position);
  vertices.Add(end_position);
  vertices.Add(end_top_position);
  vertices.Add(end_outside_top_position);
  data.vertices = vertices;


  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(1);
  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(2);
  data.triangles = triangles;

  return data;
}

// 终止点内侧面网格构建
ProceduralMeshData UWallMeshComponent::build_wall_data_section4(const WallData* wallData) {
  ProceduralMeshData data;

  FVector end_position = wallData->EndCornerPosition();
  FVector end_top_position = end_position;
  end_top_position.Z = wall_height_;

  FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector tmp = end_inside_position - end_position;
  FVector normal(-tmp.Y, tmp.X, 0);
  TArray<FVector> normals;
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  data.normals = normals;

  TArray<FVector> vertices;
  vertices.Add(end_position);
  vertices.Add(end_inside_position);
  vertices.Add(end_inside_top_position);
  vertices.Add(end_top_position);
  data.vertices = vertices;


  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(1);
  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(2);
  data.triangles = triangles;

  return data;
}

// 顶部面网格构建
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

// 底部面网格构建
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

  TArray<FVector> normals;
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  normals.Add(FVector(0, 0, 1));
  data.normals = normals;

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



// 内侧面网格构建
ProceduralMeshData UWallMeshComponent::build_wall_data_section7(const WallData* wallData, TArray<OpeningData*>& openings) {
  ProceduralMeshData data;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;    
  FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;

  TArray<FVector> vectors;
  vectors.Add(start_inside_position);
  vectors.Add(end_inside_position);
  vectors.Add(end_inside_top_position);
  vectors.Add(start_inside_top_position);
 
  build_wall_vertical_face(vectors, openings, data,75,75); 

  return data;
}

/*ProceduralMeshData UWallMeshComponent::build_wall_data_section7(const WallData* wallData, TArray<OpeningData*>& openings) {
  ProceduralMeshData data;
  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;    
  FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;

  TArray<FVector> vertices;
  vertices.Add(start_inside_position);
  vertices.Add(end_inside_position);
  vertices.Add(end_inside_top_position);
  vertices.Add(start_inside_top_position);

  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(1); 
  triangles.Add(2);

  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(3);


  FVector tmp = end_inside_position - start_inside_position;
  FVector normal(-tmp.Y, tmp.X, 0);
  TArray<FVector> normals;
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);

  TArray<FVector2D> uv0s;
  uv0s.Add(FVector2D(0.0, 0.0));
  uv0s.Add(FVector2D(0.0, 1.0));
  uv0s.Add(FVector2D(1.0, 1.0));
  uv0s.Add(FVector2D(1.0, 0.0));

  data.vertices = vertices;
  data.triangles = triangles;
  data.normals = normals;
  data.uv0s = uv0s;

  return data;
}*/

// 外侧面网格构建
ProceduralMeshData UWallMeshComponent::build_wall_data_section8(const WallData* wallData, TArray<OpeningData*>& openings) {
  ProceduralMeshData data;

  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector start_outside_top_position = start_outside_position;
  start_outside_top_position.Z = wall_height_;
  FVector end_outside_position = wallData->EndOutsidePosition();
  FVector end_outside_top_position = end_outside_position;
  end_outside_top_position.Z = wall_height_;

  TArray<FVector> vectors;
  vectors.Add(start_outside_position);
  vectors.Add(end_outside_position);
  vectors.Add(end_outside_top_position);
  vectors.Add(start_outside_top_position);

  build_wall_vertical_face(vectors, openings, data,75,75); 

  return data;
}



void UWallMeshComponent::build_opening_section(const WallData* wallData, OpeningData* openingData, ProceduralMeshData& data) {
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
    triangles.Add((i+1)%4);
    triangles.Add((i + 1) % 4);
    triangles.Add(i + 4);
    triangles.Add((i + 1) % 4+4);
  }
  
  data.triangles = triangles;

}

TArray<ProceduralMeshData> UWallMeshComponent::build_opening_sections(const WallData* wallData, TArray<OpeningData*>& openings) {
  TArray<ProceduralMeshData> mesh_datas;
  for (int i = 0; i < openings.Num(); i++) {
    ProceduralMeshData data;
    build_opening_section(wallData, openings[i], data);
    mesh_datas.Add(data);
  }
 

  return mesh_datas;
}

void UWallMeshComponent::InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings) {
  
  ClearAllMeshSections();
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/Model/wall02/Mat/07_134020_0037_mat.07_134020_0037_mat'"));
  
  UMaterialInstanceDynamic* mat_instance = CreateAndSetMaterialInstanceDynamicFromMaterial(6, mat);

  FVector start_inside_position = wallData->StartInsidePosition();
  //FVector start_inside_top_position = start_inside_position;
  //start_inside_top_position.Z = wall_height_;
  FVector end_inside_position = wallData->EndInsidePosition();
  //FVector end_inside_top_position = end_inside_position;
  //end_inside_top_position.Z = wall_height_;

  float width = FVector::Dist(end_inside_position, start_inside_position);
  TArray<FVector2D> vertices;
  vertices.Add(FVector2D(0,0));
  vertices.Add(FVector2D(width, 0));
  vertices.Add(FVector2D(width, wall_height_));
  vertices.Add(FVector2D(0, wall_height_));

  
  //TArray<FVector2D> corner_positions = GetRoomDataCornerPositions(roomData);
  float texWidth = 75, texHeight = 75;
  int uv_tile_num = SampleComputeUVTileNum(vertices, texWidth, texHeight);
  mat_instance->SetScalarParameterValue("TileScale", uv_tile_num);

  //UMaterial* material = UMaterial::GetDefaultMaterial( 0);
  //material->TwoSided = true;
  //SetMaterial(4, material);
  
  //ProceduralMeshData mesh_data0 =  build_wall_data_section1(wallData);
  //CreateMeshSectionWithData(this,0, mesh_data0);
  //SetMaterial(0, mat);

  //ProceduralMeshData mesh_data1 = build_wall_data_section2(wallData);
  //CreateMeshSectionWithData(this,1, mesh_data1);
  //SetMaterial(1, mat);

  //ProceduralMeshData mesh_data2 = build_wall_data_section3(wallData);
  //CreateMeshSectionWithData(this,2, mesh_data2);
  //SetMaterial(2, mat);

  //ProceduralMeshData mesh_data3 = build_wall_data_section4(wallData);
  //CreateMeshSectionWithData(this,3, mesh_data3);
  //SetMaterial(3, mat);

  //ProceduralMeshData mesh_data4 = build_wall_data_section5(wallData);
  //CreateMeshSectionWithData(this,4, mesh_data4); 
  //SetMaterial(4, mat);

  //ProceduralMeshData mesh_data5 = build_wall_data_section6(wallData);
  //CreateMeshSectionWithData(this,5, mesh_data5);
  //SetMaterial(5, mat);

  ProceduralMeshData mesh_data6 = build_wall_data_section7(wallData, openings);
  CreateMeshSectionWithData(this,6, mesh_data6);
  //SetMaterial(6, mat);

  /*ProceduralMeshData mesh_data7 = build_wall_data_section8(wallData, openings);
  CreateMeshSectionWithData(this,7, mesh_data7);
  SetMaterial(7, mat);*/

  TArray<ProceduralMeshData> opening_mesh_datas = build_opening_sections(wallData, openings);
  for (int i = 0; i < opening_mesh_datas.Num(); i++) {
    //CreateMeshSectionWithData(this,i + 8, opening_mesh_datas[i]);
    //SetMaterial(i + 8, mat);
  }
}





void UWallMeshComponent::InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings, const RoomData* roomData) {
  
  ClearAllMeshSections();

  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/Model/wall02/Mat/07_134020_0037_mat.07_134020_0037_mat'"));

  UMaterialInstanceDynamic* mat_instance = CreateAndSetMaterialInstanceDynamicFromMaterial(0, mat);
  FVector start_inside_position = wallData->StartInsidePosition();
  FVector end_inside_position = wallData->EndInsidePosition();
  float width = FVector::Dist(end_inside_position, start_inside_position);
  TArray<FVector2D> vertices;
  vertices.Add(FVector2D(0, 0));
  vertices.Add(FVector2D(width, 0));
  vertices.Add(FVector2D(width, wall_height_));
  vertices.Add(FVector2D(0, wall_height_));
  float texWidth = 75, texHeight = 75;
  int uv_tile_num = SampleComputeUVTileNum(vertices, texWidth, texHeight);
  mat_instance->SetScalarParameterValue("TileScale", uv_tile_num);

  std::vector<CornerData*> corner_datas = roomData->GetCorners();
  TArray<FVector2D> polygon;
  for (int i = 0; i < corner_datas.size(); i++) {
    FVector corner_position = corner_datas[i]->position();
    FVector2D position_2D(corner_position.X, corner_position.Y);
    polygon.Add(position_2D);
  }
  
  bool is_clockwise = IsClockwisePolygon(polygon);
  bool is_start_first = true;
  int start_corner_index, end_corner_index;
  for (int i = 0; i < corner_datas.size(); i++) {
    if (wallData->IsStartCorner(corner_datas[i])) {      
      start_corner_index = i;
    }
    else if (wallData->IsEndCorner(corner_datas[i])) {
      //is_start_first = false;
      //break;
      end_corner_index = i;
    }
  }

  if (abs(start_corner_index - end_corner_index) == 1) {
    if (end_corner_index < start_corner_index)
      is_start_first = false;
  }
  // 首尾相接
  else {
    if (end_corner_index > start_corner_index)
      is_start_first = false;
  }

  // build mesh
  if (!is_clockwise) {
    if (is_start_first) {
      ProceduralMeshData mesh_data = build_wall_data_section7(wallData, openings);
      CreateMeshSectionWithData(this, 0, mesh_data);
    }
    else {
      ProceduralMeshData mesh_data = build_wall_data_section8(wallData, openings);
      CreateMeshSectionWithData(this, 0, mesh_data);
    }
  }
  else {
    if (is_start_first) {
      ProceduralMeshData mesh_data = build_wall_data_section8(wallData, openings);
      CreateMeshSectionWithData(this, 0, mesh_data);
    }
    else {
      ProceduralMeshData mesh_data = build_wall_data_section7(wallData, openings);
      CreateMeshSectionWithData(this, 0, mesh_data);
    }
  }

  
}