// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Entity/CornerData.h"
#include "WallMeshComponent.h"
#include "Util/PolygonUtil.h"

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

  FVector end_outside_position = wallData->EndOutsidePosition();
  FVector tmp = end_outside_position - start_outside_position;
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

ProceduralMeshData UWallMeshComponent::build_wall_data_section2(const WallData* wallData) {
  ProceduralMeshData data;

  FVector start_position = wallData->StartCornerPosition();
  FVector start_top_position = start_position;
  start_top_position.Z = wall_height_;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;

  FVector end_inside_position = wallData->EndInsidePosition();
  FVector tmp = end_inside_position - start_inside_position;
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

ProceduralMeshData UWallMeshComponent::build_wall_data_section3(const WallData* wallData) {
  ProceduralMeshData data;

  FVector end_position = wallData->EndCornerPosition();
  FVector end_top_position = end_position;
  end_top_position.Z = wall_height_;

  FVector end_outside_position = wallData->EndOutsidePosition();
  FVector end_outside_top_position = end_outside_position;
  end_outside_top_position.Z = wall_height_;

  FVector start_outside_position = wallData->StartOutsidePosition();
  FVector tmp = end_outside_position - start_outside_position;
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

ProceduralMeshData UWallMeshComponent::build_wall_data_section4(const WallData* wallData) {
  ProceduralMeshData data;

  FVector end_position = wallData->EndCornerPosition();
  FVector end_top_position = end_position;
  end_top_position.Z = wall_height_;

  FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector tmp = end_inside_position - start_inside_position;
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
  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;    
  FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;
  //FVector z_axis(start_inside_position.Y - end_inside_position.Y, end_inside_position.X - start_inside_position.X, 0);
  FVector x_axis = end_inside_position - start_inside_position;
  FVector z_axis(0, 0, 1);
  FVector y_axis = FVector::CrossProduct(z_axis, x_axis);
  y_axis = -y_axis;
  x_axis.Normalize();
  y_axis.Normalize();
  z_axis.Normalize();
  FVector w_axis = FVector::ZeroVector;
  FMatrix mat(x_axis, y_axis, z_axis, w_axis);
  FMatrix inverse_mat = mat.Inverse();

  TArray<FVector> vectors;
  vectors.Add(start_inside_position);
  vectors.Add(end_inside_position);
  vectors.Add(end_inside_top_position);
  vectors.Add(start_inside_top_position);

  TArray<FVector2D> vectors1;
  for (int i = 0; i < vectors.Num(); i++) {
    FVector vector = vectors[i];
    FVector4 vector4 = inverse_mat.TransformVector(vector);
    FVector2D vector2d(vector4.X, vector4.Z);
    vectors1.Add(vector2d);
  }

  TArray<FVector> vectors2;
  
  for (int i = 0; i < openings.Num(); i++) {
    OpeningData* openingData = openings[i];
    float length = openingData->length();
    float half_length = length / 2.0;
    FVector opening_vertex1 = openingData->position() + half_length*x_axis;
    vectors2.Add(opening_vertex1);
    FVector opening_vertex2 = openingData->position() - half_length*x_axis;
    vectors2.Add(opening_vertex2);
    FVector opening_vertex3 = opening_vertex2 + FVector(0, 0, wall_height_);
    vectors2.Add(opening_vertex3);
    FVector opening_vertex4 = opening_vertex1 + FVector(0, 0, wall_height_);
    vectors2.Add(opening_vertex4);
  }
  TArray<FVector2D> vectors3;
  for (int i = 0; i < vectors2.Num(); i++) {
    FVector vector = vectors2[i];
    FVector4 vector4 = inverse_mat.TransformVector(vector);
    FVector2D vector2d(vector4.X, vector4.Z);
    vectors3.Add(vector2d);
  }

  TArray<FVector2D> face_points = split_face(vectors1, vectors3);

  int a = 0;


  /*FVector end_inside_position = wallData->EndInsidePosition();
  FVector end_inside_top_position = end_inside_position;
  end_inside_top_position.Z = wall_height_;

  FVector start_inside_position = wallData->StartInsidePosition();
  FVector start_inside_top_position = start_inside_position;
  start_inside_top_position.Z = wall_height_;

  //FVector start_outside_position = wallData->StartOutsidePosition();
  FVector tmp = end_inside_position - start_inside_position;
  FVector normal(-tmp.Y, tmp.X, 0);
  TArray<FVector> normals;
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  data.normals = normals;

  TArray<FVector> vertices;
  vertices.Add(end_inside_position);
  vertices.Add(start_inside_position);
  vertices.Add(start_inside_top_position);
  vertices.Add(end_inside_top_position);
  data.vertices = vertices;

  TArray<int32> triangles;
  triangles.Add(0);
  triangles.Add(2);
  triangles.Add(1);
  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(2);

  data.triangles = triangles;*/
  

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

  FVector tmp = end_outside_position - start_outside_position;
  FVector normal(-tmp.Y, tmp.X, 0);
  TArray<FVector> normals;
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  normals.Add(normal);
  data.normals = normals;

  TArray<FVector> vertices;
  vertices.Add(start_outside_position);
  vertices.Add(end_outside_position);
  vertices.Add(end_outside_top_position);
  vertices.Add(start_outside_top_position);
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

TArray<FVector2D> UWallMeshComponent::split_face(TArray<FVector2D>& face, TArray<FVector2D>& openings) {
  TArray<FVector2D> face_points;
  if (openings.Num() == 0) {
    face_points = face;
    return face_points;
  }

  TArray<float> x_tokens,y_tokens;

  FVector2D face_vec1 = face[0];
  FVector2D face_vec2 = face[2];
  x_tokens.Add(face_vec1.X);
  x_tokens.Add(face_vec2.X);
  y_tokens.Add(face_vec1.Y);
  y_tokens.Add(face_vec2.Y);

  int opening_num = openings.Num() / 4;
  for (int i = 0; i < opening_num; i++) {
    FVector2D vec1 = openings[4 * i];
    FVector2D vec2 = openings[4 * i + 2];
    
    x_tokens.Add(vec1.X);
    x_tokens.Add(vec2.X);

    
    y_tokens.Add(vec1.Y);
    y_tokens.Add(vec2.Y);
  }
  x_tokens.HeapSort();
  y_tokens.HeapSort();

  for (int i = 1; i < y_tokens.Num(); i++) {
    float y_token = y_tokens[i];
    float pre_y_token = y_tokens[i - 1];
    if (y_token == pre_y_token) {
      continue;
    }
    for (int j = 1; j < x_tokens.Num(); j++) {
      float x_token = x_tokens[j];
      float pre_x_token = x_tokens[j - 1];
      if (x_token == pre_x_token) {
        continue;
      }
      FVector2D vec1(pre_x_token, pre_y_token);      
      FVector2D vec2(x_token, pre_y_token);
      FVector2D vec3(x_token,y_token);
      FVector2D vec4(pre_x_token, y_token);
      bool is_opening = true;
      int index1 = openings.Find(vec1);
      if (index1 == INDEX_NONE) {
        is_opening = false;
      }

      int index2 = openings.Find(vec2);
      if (index2 == INDEX_NONE) {
        is_opening = false;
      }

      int index3 = openings.Find(vec3);
      if (index3 == INDEX_NONE) {
        is_opening = false;
      }

      int index4 = openings.Find(vec4);
      if (index4 == INDEX_NONE) {
        is_opening = false;
      }

      int max = -1;
      int min = openings.Num();
      max = max > index1 ? max : index1;
      max = max > index2 ? max : index2;
      max = max > index3 ? max : index3;
      max = max > index4 ? max : index4;

      min = min < index1 ? min : index1;
      min = min < index2 ? min : index2;
      min = min < index3 ? min : index3;
      min = min < index4 ? min : index4;

      if (max - min != 3 || max % 4 != 3 || min % 4 != 0) {
        is_opening = false;
      }

      if (is_opening == false) {
        face_points.Add(vec1);
        face_points.Add(vec2);
        face_points.Add(vec3);
        face_points.Add(vec4);
      }


    }
  }


  return face_points;
}

TArray<ProceduralMeshData> UWallMeshComponent::build_opening_sections(const WallData* wallData, TArray<OpeningData*>& openings) {
  TArray<ProceduralMeshData> mesh_datas;




  return mesh_datas;
}

void UWallMeshComponent::InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings) {
  
  ClearAllMeshSections();
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/WallDefaultMat.WallDefaultMat'"));
  //UMaterial* material = UMaterial::GetDefaultMaterial( 0);
  //material->TwoSided = true;
  //SetMaterial(4, material);
  
  ProceduralMeshData mesh_data0 =  build_wall_data_section1(wallData);
  CreateMeshSectionWithData(0, mesh_data0);
  SetMaterial(0, mat);

  ProceduralMeshData mesh_data1 = build_wall_data_section2(wallData);
  CreateMeshSectionWithData(1, mesh_data1);
  SetMaterial(1, mat);

  ProceduralMeshData mesh_data2 = build_wall_data_section3(wallData);
  CreateMeshSectionWithData(2, mesh_data2);
  SetMaterial(2, mat);

  ProceduralMeshData mesh_data3 = build_wall_data_section4(wallData);
  CreateMeshSectionWithData(3, mesh_data3);
  SetMaterial(3, mat);

  ProceduralMeshData mesh_data4 = build_wall_data_section5(wallData);
  CreateMeshSectionWithData(4, mesh_data4); 
  SetMaterial(4, mat);

  ProceduralMeshData mesh_data5 = build_wall_data_section6(wallData);
  CreateMeshSectionWithData(5, mesh_data5);
  SetMaterial(5, mat);

  ProceduralMeshData mesh_data6 = build_wall_data_section7(wallData, openings);
  CreateMeshSectionWithData(6, mesh_data6);
  SetMaterial(6, mat);

  ProceduralMeshData mesh_data7 = build_wall_data_section8(wallData, openings);
  CreateMeshSectionWithData(7, mesh_data7);
  SetMaterial(7, mat);
}

