// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Entity/WallData.h"
#include "Entity/CornerData.h"
#include "Util/PolygonUtil.h"
#include "OutsideWallMeshComponent.h"



void UOutsideWallMeshComponent::InitWithDesignData(DesignData* designData) {
  UMaterial* mat = LoadObject<UMaterial>(NULL, TEXT("Material'/Game/Model/wall02/Mat/07_134020_0037_mat.07_134020_0037_mat'"));
  UMaterialInstanceDynamic* mat_instance = CreateAndSetMaterialInstanceDynamicFromMaterial(0, mat);
  ProceduralMeshData mesh_data = build_mesh_section(designData);
  CreateMeshSectionWithData(this, 0, mesh_data);
}

ProceduralMeshData UOutsideWallMeshComponent::build_mesh_section(DesignData* designData) {
  ProceduralMeshData data;
  TArray<WallData*> outside_walls = designData->GetOutsideWalls();
  TArray<FVector2D> outside_corner_position;

  for (int i = 0; i < outside_walls.Num(); i++) {
    int j = (i + 1) % outside_walls.Num();
    CornerData* corner = outside_walls[i]->GetConnectedCorner(outside_walls[j]);
    FVector tmp = corner->position();
    FVector2D position(tmp.X, tmp.Y);
    outside_corner_position.Add(position);
  }

  bool is_clockwise = IsClockwisePolygon(outside_corner_position);

  TArray<FVector2D> outside_position;
  for (int i = 0; i < outside_walls.Num(); i++) {
    int j = (i + 1) % outside_walls.Num();
    CornerData* corner = outside_walls[i]->GetConnectedCorner(outside_walls[j]);
    FVector tmp;
    if (outside_walls[i]->IsStartCorner(corner)) {
      if (is_clockwise) {
        tmp = outside_walls[i]->StartOutsidePosition();
      }
      else {
        tmp = outside_walls[i]->StartInsidePosition();
      }
    }
    else {
      if (is_clockwise) {
        tmp = outside_walls[i]->EndInsidePosition();
      }
      else {
        tmp = outside_walls[i]->EndOutsidePosition();
      }
    }
    outside_position.Add(FVector2D(tmp.X,tmp.Y));
  }

  float height = 295;
  float bottom = -5;

  int outside_wall_num = outside_walls.Num();
  int uv_row_num = outside_wall_num / 2 + outside_wall_num % 2;

  // build vertical wall mesh
  for (int i = 0; i < outside_walls.Num(); i++) {
    int wall_index = (i + 1) % outside_walls.Num();
    WallData* wall = outside_walls[wall_index];
    TArray<OpeningData*> openings = designData->GetRelatedOpenings(wall);

    ProceduralMeshData tmp_data;
    int start_index = i;
    int end_index = wall_index;

    TArray<FVector> vectors;
    vectors.Add(FVector(outside_position[start_index], bottom));
    vectors.Add(FVector(outside_position[end_index], bottom));
    vectors.Add(FVector(outside_position[end_index], height));
    vectors.Add(FVector(outside_position[start_index], height));

    build_wall_vertical_face(vectors, openings, tmp_data,75,75);

    float v_scale = 0.6 / uv_row_num*0.9;
    float u_scale = 0.5*0.9;
    float v_offset = (int)(i / 2)*(0.6 / uv_row_num);
    float u_offset = (int)(i % 2)*0.5;
    for (int j = 0; j < tmp_data.uv0s.Num(); j++) {
      tmp_data.uv0s[j].X = u_scale*tmp_data.uv0s[j].X + u_offset;
      tmp_data.uv0s[j].Y = v_scale*tmp_data.uv0s[j].Y + v_offset;
    }
    data.Append(tmp_data);
  }
  //TArray<FVector2D> tmp_vecs;
  TArray<FVector2D> uv_rect = GetUVRect(outside_position,75,75);


  TArray<FVector2D> tmp_vecs = Triangulation(outside_position);

  
  float u_scale = 0.9*0.5;
  float u_offset = 0.0;
  float v_scale = 0.4;
  float v_offset = 0.6;
  for (int i = 0; i < tmp_vecs.Num() ; i++) {
    data.triangles.Add(data.vertices.Num());
    data.vertices.Add(FVector(tmp_vecs[i], bottom));


    /*data.triangles.Add(data.vertices.Num());
    data.vertices.Add(FVector(tmp_vecs[3 * i + 1], bottom));
    data.triangles.Add(data.vertices.Num());
    data.vertices.Add(FVector(tmp_vecs[3 * i + 0], bottom));*/
    
    FVector2D uv = ComputeUV(uv_rect, tmp_vecs[i]);
    uv.X = u_scale*uv.X + u_offset;
    uv.Y = v_scale*uv.Y + v_offset;
    data.uv0s.Add(uv);
    data.normals.Add(FVector(0, 0, 1));
    /*data.normals.Add(FVector(0, 0, 1));
    data.normals.Add(FVector(0, 0, 1));*/
    
    
  }

  u_scale = 0.9*0.5;
  u_offset = 0.5;
  v_scale = 0.4;
  v_offset = 0.6;
  for (int i = 0; i < tmp_vecs.Num() ; i++) {
    data.triangles.Add(data.vertices.Num());
    data.vertices.Add(FVector(tmp_vecs[ i ], height));
    /*data.triangles.Add(data.vertices.Num());
    data.vertices.Add(FVector(tmp_vecs[3 * i + 1], height));
    data.triangles.Add(data.vertices.Num());
    data.vertices.Add(FVector(tmp_vecs[3 * i + 0], height));
    */
    FVector2D uv = ComputeUV(uv_rect, tmp_vecs[i]);
    uv.X = u_scale*uv.X + u_offset;
    uv.Y = v_scale*uv.Y + v_offset;
    data.uv0s.Add(uv);
    data.normals.Add(FVector(0, 0, -1));
    /*data.normals.Add(FVector(0, 0, -1));
    data.normals.Add(FVector(0, 0, -1));*/

    
  }

  return data;
}


