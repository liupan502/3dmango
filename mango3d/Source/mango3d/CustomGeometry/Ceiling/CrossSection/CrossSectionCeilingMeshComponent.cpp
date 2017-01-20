// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Util/PolygonUtil.h"
#include "CrossSectionCeilingMeshComponent.h"

void UCrossSectionCeilingMeshComponent::InitWithCrossSectionCeilingData(CrossSectionCeilingData* data,RoomData* roomData) {
  
  ClearAllMeshSections();
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/Model/top/Mat/Mat_4.Mat_4'"));
  UMaterialInstanceDynamic* mat_instance = CreateAndSetMaterialInstanceDynamicFromMaterial(0, mat);
  ProceduralMeshData mesh_data = build_mesh_section(data, roomData);
  CreateMeshSectionWithData(this, 0, mesh_data);
}

ProceduralMeshData UCrossSectionCeilingMeshComponent::build_mesh_section(CrossSectionCeilingData* ceilingData,RoomData* roomData) {
  ProceduralMeshData data;
  
  TArray<FVector> inner_wall_points = roomData->InnerWallPoints();
  TArray<FVector2D> tmp;
  for (int i = 0; i < inner_wall_points.Num(); i++) {
    FVector2D vec(inner_wall_points[i].X, inner_wall_points[i].Y);
    tmp.Add(vec);
  }

  bool is_clockwise = IsClockwisePolygon(tmp);
  std::vector<BaseCeilingUnit*> units = ceilingData->ceiling_units();

  // 计算uv 的缩放因子
  int unit_size = units.size();
  int point_size = inner_wall_points.Num();
  float big_step = 0.01;
  float little_step = 0.01;

  float value1 = 1.0 - 0.05 * 2 + (point_size - 1)*big_step + (unit_size - 1)*point_size*little_step;
  float unit_width = 0.0;
  float max_unit_distance = 0.0;
  for (int i = 0; i < unit_size; i++) {
    unit_width += units[i]->width();
    if (max_unit_distance < units[i]->width()) {
      max_unit_distance = units[i]->width();
    }
  }
  unit_width *= point_size;
  float scale1 = value1 / unit_width;

  float max_distance = 0.0;
  for (int i = 0; i < point_size; i++) {
    int j = (i + 1) % point_size;
    float distance = FVector::Dist(inner_wall_points[i], inner_wall_points[j]);
    if (max_distance < distance)
      max_distance = distance;
  }

  max_distance += (2 * max_unit_distance);
  float scale2 = 0.9 / max_distance;
  float scale = scale1 > scale2 ? scale2 : scale1;

  FVector2D uv_offset = FVector2D(0.05, 0.05);
  for (int i = 0; i < inner_wall_points.Num(); i++) {
    int j = (i + 1) % inner_wall_points.Num();
    TArray<FVector> points;
    points.Add(inner_wall_points[i]);
    points.Add(inner_wall_points[(i + 1) % inner_wall_points.Num()]);
    points.Add(inner_wall_points[(i + 2) % inner_wall_points.Num()]);
    points.Add(inner_wall_points[(i + 3) % inner_wall_points.Num()]);
    
    for (int k = 0; k < units.size(); k++) {
      BaseCeilingUnit* unit = units[k];
      
      switch (unit->ceiling_unit_type()) {
      case CEILING_UNIT_LINE: {
        ProceduralMeshData unit_data = build_line_unit_mesh_section(
          (LineCeilingUnit*)unit, points, is_clockwise, uv_offset, scale);
        data.Append(unit_data);
        uv_offset += FVector2D(0.0, unit->width()*scale);
      }
        break;
      default:
        break;

      }

      if (k != (units.size() - 1)) {
        uv_offset += FVector2D(0.0, little_step);
      }
    }

    uv_offset += FVector2D(0.0, big_step);
    

  }
  return data;
}

ProceduralMeshData UCrossSectionCeilingMeshComponent::build_line_unit_mesh_section(
  LineCeilingUnit* unit,  TArray<FVector> points, bool isClockwise, FVector2D uvOffset, float scale) {
  ProceduralMeshData data;
  if (!isClockwise) {
    int point_num = points.Num();
    for (int i = 0; i < points.Num() / 2; i++) {
      FVector tmp = points[i];
      points[i] = points[point_num - 1 - i];
      points[point_num - 1 - i] = tmp;
    }
  }

  FVector p0 = points[0];
  FVector p1 = points[1];
  FVector p2 = points[2];
  FVector p3 = points[3];
  FVector vec1 =  p1 - p2;
  float length = FVector::Dist(p1,p2);
  
  // new x axis
  vec1.Normalize();

  // new y axis
  FVector vec2(vec1.Y, -vec1.X, 0);

  // new z axis
  FVector vec3(0, 0, 1);

  FVector origin =  p1;
  FBasisVectorMatrix matrix(vec1,vec2,vec3, origin);

  FVector v01 = p1 - p0;
  FVector normal_v01(v01.Y, -v01.X, v01.Z);
  normal_v01.Normalize();
  FVector v12 = p2 - p1;
  FVector normal_v12(v12.Y, -v12.X, v12.Z);
  normal_v12.Normalize();
  FVector v23 = p3 - p2;
  FVector normal_v23(v23.Y, -v23.X, v23.Z);
  normal_v23.Normalize();

  FVector tmp_start_point = unit->start_point();
  tmp_start_point.Y = -tmp_start_point.Y;  
  float start_offset = tmp_start_point.X;
  FVector start_point = p1+start_offset*(normal_v01+normal_v12) + FVector(0,0,280)+FVector(0.0,0.0,tmp_start_point.Y);
  FVector start_inside_point = p2 + start_offset*(normal_v12 + normal_v23) + FVector(0, 0, 280) + FVector(0.0, 0.0, tmp_start_point.Y);
  
  FVector tmp_end_point = unit->end_point();
  tmp_end_point.Y = -tmp_end_point.Y;
  float end_offset = tmp_end_point.X;
  FVector end_point = p1 + end_offset*(normal_v01 + normal_v12) + FVector(0, 0, 280) + FVector(0.0, 0.0, tmp_end_point.Y);
  FVector end_inside_point = p2 + end_offset*(normal_v12 + normal_v23) + FVector(0, 0, 280) + FVector(0.0, 0.0, tmp_end_point.Y);

  /*FVector4 start_point_4 = matrix.TransformPosition(start_point);
  FVector4 start_inside_point_4 = matrix.TransformPosition(start_inside_point);
  FVector4 end_point_4 = matrix.TransformPosition(end_point);
  FVector4 end_inside_point_4 = matrix.TransformPosition(end_inside_point);

  start_point = FVector(start_point_4.X, start_point_4.Y, start_point_4.Z);
  start_inside_point = FVector(start_inside_point_4.X,start_inside_point_4.Y,start_inside_point_4.Z);
  end_point = FVector(end_point_4.X, end_point_4.Y, end_point_4.Z);
  end_inside_point = FVector(end_inside_point_4.X, end_inside_point_4.Y, end_inside_point_4.Z);
  */
  TArray<FVector> vertices;
  vertices.Add(end_point);
  vertices.Add(start_point);
  vertices.Add(start_inside_point);
  vertices.Add(end_inside_point);
  data.vertices = vertices;
  

  TArray<int> triangles;
  triangles.Add(2);
  triangles.Add(1);
  triangles.Add(0);
  triangles.Add(3);
  triangles.Add(2);
  triangles.Add(0);
  data.triangles = triangles;

  FVector normal = FVector::CrossProduct(end_point - start_point, vec1);
  normal.Normalize();

  TArray<FVector> normals;
  TArray<FProcMeshTangent> tangents;
  for (int i = 0; i < 4; i++) {
    normals.Add(normal);
    tangents.Add(FProcMeshTangent(vec1, false));
  }
  data.normals = normals;
  data.tangents = tangents;
  
  TArray<FVector2D> uv0s;
  FVector end_to_end_inside = end_inside_point - end_point;
  FVector end_to_start = start_point - end_point;
  FVector end_to_start_inside = start_inside_point - end_point;

  end_to_end_inside.Normalize();
  end_to_start.Normalize();
  end_to_start_inside.Normalize();

  float val1 = acos(FVector::DotProduct(end_to_end_inside, end_to_start));
  float val2 = acos(FVector::DotProduct(end_to_end_inside, end_to_start_inside));

  float dist_end_to_end_inside = FVector::Dist(end_point, end_inside_point);
  float dist_end_to_start = FVector::Dist(end_point, start_point);
  float dist_end_to_start_inside = FVector::Dist(end_point, start_inside_point);

  TArray<FVector2D> polygon;
  FVector2D new_end_point(0.0, 0.0);
  polygon.Add(new_end_point);
  FVector2D new_end_inside_point(dist_end_to_end_inside, 0.0);
  polygon.Add(new_end_inside_point);
  FVector2D new_start_point = dist_end_to_start*FVector2D(cos(val1),sin(val1));
  polygon.Add(new_start_point);
  FVector2D new_start_inside_point = dist_end_to_start_inside*FVector2D(cos(val2), sin(val2));
  polygon.Add(new_start_inside_point);

  FVector2D left_top_point = polygon[0];
  for (int i = 0; i < polygon.Num(); i++) {
    FVector2D tmp_point = polygon[i];
    if (tmp_point.X < left_top_point.X) {
      left_top_point.X = tmp_point.X;
    }

    if (tmp_point.Y > left_top_point.Y) {
      left_top_point.Y = tmp_point.Y;
    }
  }


  FVector2D end_uv = (new_end_point - left_top_point)*scale;
  end_uv.Y = -end_uv.Y;
  uv0s.Add(end_uv + uvOffset) ;

  FVector2D start_uv = (new_start_point - left_top_point)*scale;
  start_uv.Y = -start_uv.Y;
  uv0s.Add(start_uv + uvOffset);

  FVector2D start_inside_uv = (new_start_inside_point - left_top_point)*scale;
  start_inside_uv.Y = -start_inside_uv.Y;
  uv0s.Add(start_inside_uv + uvOffset);

  FVector2D end_inside_uv = (new_end_inside_point - left_top_point)*scale;
  end_inside_uv.Y = -end_inside_uv.Y;
  uv0s.Add(end_inside_uv + uvOffset);

  data.uv0s = uv0s;
  return data;
}



