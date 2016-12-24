// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Entity/RoomData.h"
#include "Entity/CornerData.h"
#include "Entity/WallData.h"
#include "Entity/OpeningData.h"
#include "Util/CustomGeometryUtil.h"
#include "Util/PolygonUtil.h"
#include "SkirtingLineMeshComponent.h"

void USkirtingLineMeshComponent::InitWithWallData(WallData* wallData, TArray<OpeningData*>& openings, RoomData* roomData) {
  ClearAllMeshSections();
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/Model/wall/Mat/Mat_2.Mat_2'"));
  UMaterialInstanceDynamic* mat_instance = CreateAndSetMaterialInstanceDynamicFromMaterial(0, mat);
  ProceduralMeshData mesh_data = build_mesh_section(wallData, openings,roomData);
  CreateMeshSectionWithData(this, 0, mesh_data);
}

ProceduralMeshData USkirtingLineMeshComponent::build_mesh_section
(WallData* wallData, TArray<OpeningData*>& openings, RoomData* roomData) {
  ProceduralMeshData data;
  

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
  // Ê×Î²Ïà½Ó
  else {
    if (end_corner_index > start_corner_index)
      is_start_first = false;
  }

  FVector start_position, end_position;
  if (is_clockwise) {
    if (is_start_first) {
      start_position = wallData->StartOutsidePosition();
      end_position = wallData->EndOutsidePosition();
    }
    else {
      start_position = wallData->EndOutsidePosition();
      end_position = wallData->StartOutsidePosition();
    }
  }
  else {
    if (is_start_first) {
      start_position = wallData->StartInsidePosition();
      end_position = wallData->EndInsidePosition();
    }
    else {
      start_position = wallData->EndInsidePosition();
      end_position = wallData->StartInsidePosition();
    }
  }
  FVector direction = end_position - start_position;
  direction.Normalize();
  FVector normal_direction(-direction.Y, direction.X, direction.Z);

  // sort opening
  for (int i = 0; i < openings.Num(); i++) {
    for (int j = 0; j < openings.Num(); j++) {
      OpeningData* opening1 = openings[i];
      OpeningData* opening2 = openings[j];
      float dist1 = FVector::Dist(start_position, opening1->position());
      float dist2 = FVector::Dist(start_position, opening2->position());
      if (dist2 < dist1) {
        OpeningData* tmp = openings[i];
        openings[i] = openings[j];
        openings[j] = tmp;
      }
    }
  }
  
  TArray<FVector> points;
  points.Add(start_position);
  for (int i = 0; i < openings.Num(); i++) {
    OpeningData* opening_data = openings[i];
    float half_length = opening_data->length()/2.0;
    FVector opening_position = opening_data->position();
    FVector pos1 = opening_position - half_length*direction;
    FVector pos2 = opening_position + half_length*direction;
    float half_wall_width = wallData->width()/2.0;
    pos1 = pos1 + half_wall_width*normal_direction;
    pos2 = pos2 + half_wall_width*normal_direction;
    points.Add(pos1);
    points.Add(pos2);
  }
  points.Add(end_position);
  int segment_num = points.Num() / 2;
  TArray<FVector> vertices;
  TArray<FVector> normals;
  TArray<FProcMeshTangent> tangents;
  TArray<int> triangles;
  TArray<FVector2D> uv0s;
  float v_step = 0.9 / segment_num;
  for (int i = 0; i < segment_num; i++) {
    FVector pos1 = points[2*i];
    FVector pos2 = points[2 * i + 1];


    FVector2D uv_offset = FVector2D(0.05, 0.05 + v_step*i);
    
    // bottom face
    int index_offset = vertices.Num();
    vertices.Add(pos1);
    vertices.Add(pos1 + normal_direction*skirting_line_width_);
    vertices.Add(pos2 + normal_direction*skirting_line_width_);
    vertices.Add(pos2);

    normals.Add(FVector(0, 0, -1));
    normals.Add(FVector(0, 0, -1));
    normals.Add(FVector(0, 0, -1));
    normals.Add(FVector(0, 0, -1));

    tangents.Add(FProcMeshTangent(-direction,false));
    tangents.Add(FProcMeshTangent(-direction,false));
    tangents.Add(FProcMeshTangent(direction,false));
    tangents.Add(FProcMeshTangent(direction,false));

    
    triangles.Add(0 + index_offset);
    triangles.Add(1 + index_offset);
    triangles.Add(2 + index_offset);

    triangles.Add(0 + index_offset);
    triangles.Add(2 + index_offset);
    triangles.Add(3 + index_offset);

    
    uv0s.Add(FVector2D(0.0,0.0)+uv_offset);
    uv0s.Add(FVector2D(0.0, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.13, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.13, 0.0) + uv_offset);

    //top face
    index_offset = vertices.Num();
    FVector z_offset = FVector(0.0,0.0,skirting_line_height_);
    vertices.Add(pos1+z_offset);
    vertices.Add(pos1 + normal_direction*skirting_line_width_+ z_offset);
    vertices.Add(pos2 + normal_direction*skirting_line_width_+ z_offset);
    vertices.Add(pos2 + z_offset);

    normals.Add(FVector(0, 0, 1));
    normals.Add(FVector(0, 0, 1));
    normals.Add(FVector(0, 0, 1));
    normals.Add(FVector(0, 0, 1));

    
    
    tangents.Add(FProcMeshTangent(-direction,false));
    tangents.Add(FProcMeshTangent(-direction,false));
    tangents.Add(FProcMeshTangent(direction,false));
    tangents.Add(FProcMeshTangent(direction,false));

    
    triangles.Add(0 + index_offset);
    triangles.Add(1 + index_offset);
    triangles.Add(2 + index_offset);

    triangles.Add(0 + index_offset);
    triangles.Add(2 + index_offset);
    triangles.Add(3 + index_offset);


    uv0s.Add(FVector2D(0.15, 0.0) + uv_offset);
    uv0s.Add(FVector2D(0.15, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.28, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.28, 0.0) + uv_offset);

    // front face
    //FVector z_offset = FVector(0.0, 0.0, skirting_line_height_);
    index_offset = vertices.Num();
    vertices.Add(pos1 + normal_direction*skirting_line_width_+z_offset);
    vertices.Add(pos1 + normal_direction*skirting_line_width_ );
    vertices.Add(pos2 + normal_direction*skirting_line_width_);
    vertices.Add(pos2 + normal_direction*skirting_line_width_ + z_offset);    

    normals.Add(normal_direction);
    normals.Add(normal_direction);
    normals.Add(normal_direction);
    normals.Add(normal_direction);

    tangents.Add(FProcMeshTangent(-direction,false));
    tangents.Add(FProcMeshTangent (-direction,false));
    tangents.Add(FProcMeshTangent(direction,false));
    tangents.Add(FProcMeshTangent(direction,false));

    //index_offset = triangles.Num();
    triangles.Add(0 + index_offset);
    triangles.Add(1 + index_offset);
    triangles.Add(2 + index_offset);

    triangles.Add(0 + index_offset);
    triangles.Add(2 + index_offset);
    triangles.Add(3 + index_offset);


    uv0s.Add(FVector2D(0.30, 0.0) + uv_offset);
    uv0s.Add(FVector2D(0.30, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.43, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.43, 0.0) + uv_offset);

    // back face
    //FVector z_offset = FVector(0.0, 0.0, skirting_line_height_);
    index_offset = vertices.Num();
    vertices.Add(pos1 + z_offset);
    vertices.Add(pos1 );
    vertices.Add(pos2 );
    vertices.Add(pos2 + z_offset);

    normals.Add(-normal_direction);
    normals.Add(-normal_direction);
    normals.Add(-normal_direction);
    normals.Add(-normal_direction);

    tangents.Add(FProcMeshTangent(-direction,false));
    tangents.Add(FProcMeshTangent(-direction,false));
    tangents.Add(FProcMeshTangent(direction,false));
    tangents.Add(FProcMeshTangent(direction,false));

    //index_offset = triangles.Num();
    triangles.Add(0 + index_offset);
    triangles.Add(1 + index_offset);
    triangles.Add(2 + index_offset);

    triangles.Add(0 + index_offset);
    triangles.Add(2 + index_offset);
    triangles.Add(3 + index_offset);


    uv0s.Add(FVector2D(0.45, 0.0) + uv_offset);
    uv0s.Add(FVector2D(0.45, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.58, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.58, 0.0) + uv_offset);

    // left face
    //FVector z_offset = FVector(0.0, 0.0, skirting_line_height_);
    index_offset = vertices.Num();
    vertices.Add(pos1 + z_offset);
    vertices.Add(pos1);
    vertices.Add(pos1 + normal_direction*skirting_line_width_);
    vertices.Add(pos1 + normal_direction*skirting_line_width_ + z_offset);

    normals.Add(-direction);
    normals.Add(-direction);
    normals.Add(-direction);
    normals.Add(-direction);

    tangents.Add(FProcMeshTangent(-normal_direction,false));
    tangents.Add(FProcMeshTangent(-normal_direction,false));
    tangents.Add(FProcMeshTangent(normal_direction,false));
    tangents.Add(FProcMeshTangent(normal_direction,false));

    //index_offset = triangles.Num();
    triangles.Add(0 + index_offset);
    triangles.Add(1 + index_offset);
    triangles.Add(2 + index_offset);

    triangles.Add(0 + index_offset);
    triangles.Add(2 + index_offset);
    triangles.Add(3 + index_offset);


    uv0s.Add(FVector2D(0.60, 0.0) + uv_offset);
    uv0s.Add(FVector2D(0.60, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.73, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.73, 0.0) + uv_offset);

    // right face
    //FVector z_offset = FVector(0.0, 0.0, skirting_line_height_);    
    index_offset = vertices.Num();
    vertices.Add(pos2 + normal_direction*skirting_line_width_ + z_offset);
    vertices.Add(pos2 + normal_direction*skirting_line_width_);
    vertices.Add(pos2);
    vertices.Add(pos2 + z_offset);

    normals.Add(direction);
    normals.Add(direction);
    normals.Add(direction);
    normals.Add(direction);

    tangents.Add(FProcMeshTangent(normal_direction,false));
    tangents.Add(FProcMeshTangent(normal_direction,false));
    tangents.Add(FProcMeshTangent(-normal_direction,false));
    tangents.Add(FProcMeshTangent(-normal_direction,false));

    //index_offset = triangles.Num();
    triangles.Add(0 + index_offset);
    triangles.Add(1 + index_offset);
    triangles.Add(2 + index_offset);

    triangles.Add(0 + index_offset);
    triangles.Add(2 + index_offset);
    triangles.Add(3 + index_offset);


    uv0s.Add(FVector2D(0.75, 0.0) + uv_offset);
    uv0s.Add(FVector2D(0.75, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.88, v_step) + uv_offset);
    uv0s.Add(FVector2D(0.88, 0.0) + uv_offset);
    
   

  }

  data.vertices = vertices;
  data.normals = normals;
  data.tangents = tangents;
  data.uv0s = uv0s;
  data.triangles = triangles;

  return data;
}




