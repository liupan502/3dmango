#include "mango3d.h"
#include "CustomGeometryUtil.h"
#include "Entity/RoomData.h"
#include "Entity/CornerData.h"
#include "Entity/WallData.h"
#include "Entity/OpeningData.h"
#include "PolygonUtil.h"
#include "RawMesh.h"
#include <vector>

void CreateMeshSectionWithData(UProceduralMeshComponent* umc, int sectionIndex, ProceduralMeshData& data) {
  umc->CreateMeshSection(sectionIndex, data.vertices, data.triangles,
    data.normals, data.uv0s, data.vertex_colors,
    data.tangents, data.bool_value);
}

TArray<FVector2D> BuildRoomMesh(const RoomData* roomData) {
  

  /*std::vector<CornerData*> corners = roomData->GetCorners();
  TArray<FVector2D> corner_vertices;
  for (size_t i = 0; i < corners.size(); i++) {
    FVector tmp = corners[i]->position();
    FVector2D corner_vertex(tmp.X, tmp.Y);
    corner_vertices.Add(corner_vertex);
  }
  TArray<FVector2D> corner_vertices = roomData->GetCornerPositions();*/
  //TArray<FVector2D> corner_vertices = GetRoomDataCornerPositions(roomData);
  TArray<FVector2D> corner_vertices = roomData->GetCornerPositions();
  TArray<FVector2D> result = Triangulation(corner_vertices);
  return result;
}

TArray<FVector2D> GetRoomDataCornerPositions(const RoomData* roomData) {
  TArray<FVector2D> corner_vertices;
  const std::vector<WallData*> walls = roomData->GetWalls();
  for (int i = 0; i < walls.size(); i++) {
    int j = (i + 1) % walls.size();
    WallData* wall = walls[i];
    WallData* next_wall = walls[j];
    CornerData* corner = wall->GetConnectedCorner(next_wall);
    if (wall->IsStartCorner(corner)) {
      FVector tmp = wall->StartOutsidePosition();
      corner_vertices.Add(FVector2D(tmp.X, tmp.Y));
    }
    else {
      FVector tmp = wall->EndOutsidePosition();
      corner_vertices.Add(FVector2D(tmp.X, tmp.Y));
    }
  }

  return corner_vertices;
}



struct Rect {
  FVector2D center;
  float width;
  float height;

  Rect(const FVector2D& point, float width, float height) {
    this->center = point;
    this->width = width;
    this->height = height;
  }

  bool operator ==(const Rect& rect) {
    if (center != rect.center)
      return false;
    if (width != rect.width)
      return false;
    if (height != rect.height)
      return false;
    return true;
  }

  TArray<FVector2D> points() {
    TArray<FVector2D> points;
    float half_width = width / 2.0;
    float half_height = height / 2.0;

    // left top point
    points.Add(center + FVector2D(-half_width, -half_height));

    // right top point
    points.Add(center + FVector2D(half_width, -half_height));

    // right bottom point
    points.Add(center + FVector2D(half_width, half_height));

    // left bottom point
    points.Add(center + FVector2D(-half_width, half_height));
    return points;
  }
};

bool contain_rect(TArray<Rect>& rects, const Rect& rect)  {
  for (int i = 0; i < rects.Num();i++) {
    if ( rects[i] == rect) {
      return true;
    }
  }
  return false;
}

TArray<FVector2D> BuildRoomMesh(const RoomData* roomData, float texWidth, float texLength) {  
  TArray<FVector2D> vertices;
  TArray<FVector2D> corner_vertices = roomData->GetCornerPositions();  
  FVector2D start_vertex = corner_vertices[0];
  Rect first_rect(start_vertex, texWidth, texLength);
  TArray<Rect> inside_rects;
  TArray<Rect> rects;
  rects.Add(first_rect);
  bool is_first_time = true;
  while (rects.Num() > 0) {
    Rect rect = rects[0];
    rects.RemoveAt(0);
    int status;

    // 第一次要检查初始的矩形是否需要计算
    if (is_first_time) {
      is_first_time = false;
      status = IsPolygonInPolygon(rect.points(), corner_vertices);
      if (status != -1) {
        inside_rects.Add(rect);
      }
    }
    
    Rect top_rect(rect.center+FVector2D(0,-texLength),texWidth, texLength);
    status = IsPolygonInPolygon(top_rect.points(), corner_vertices);
    if (status != -1) {  
      if (!contain_rect(inside_rects,top_rect)) {
        rects.Add(top_rect);
        inside_rects.Add(top_rect);
      }     
    }

    Rect left_rect(rect.center + FVector2D(-texWidth, 0), texWidth, texLength);
    status = IsPolygonInPolygon(left_rect.points(), corner_vertices);
    if (status != -1 ) {
      if (!contain_rect(inside_rects, left_rect)) {
        rects.Add(left_rect);
        inside_rects.Add(left_rect);
      }      
    }

    Rect right_rect(rect.center + FVector2D(texWidth, 0), texWidth, texLength);
    status = IsPolygonInPolygon(right_rect.points(), corner_vertices);
    if (status != -1) {
      if (!contain_rect(inside_rects, right_rect)) {
        rects.Add(right_rect);
        inside_rects.Add(right_rect);
      }      
    }

    Rect bottom_rect(rect.center + FVector2D(0, texLength), texWidth, texLength);
    status = IsPolygonInPolygon(bottom_rect.points(), corner_vertices);
    if (status != -1) {
      if (!contain_rect(inside_rects, bottom_rect)) {
        rects.Add(bottom_rect);
        inside_rects.Add(bottom_rect);
      }      
    }
    
    Rect left_top_rect(rect.center + FVector2D(-texWidth, -texLength), texWidth, texLength);
    status = IsPolygonInPolygon(left_top_rect.points(), corner_vertices);
    if (status != -1) {
      if (!contain_rect(inside_rects, left_top_rect)) {
        rects.Add(left_top_rect);
        inside_rects.Add(left_top_rect);
      }
    }

    Rect right_top_rect(rect.center + FVector2D(texWidth, -texLength), texWidth, texLength);
    status = IsPolygonInPolygon(right_top_rect.points(), corner_vertices);
    if (status != -1) {
      if (!contain_rect(inside_rects, right_top_rect)) {
        rects.Add(right_top_rect);
        inside_rects.Add(right_top_rect);
      }      
    }

    Rect right_bottom_rect(rect.center + FVector2D(texWidth, texLength), texWidth, texLength);
    status = IsPolygonInPolygon(right_bottom_rect.points(), corner_vertices);
    if (status != -1 ) {
      if (!contain_rect(inside_rects, right_bottom_rect)) {
        rects.Add(right_bottom_rect);
        inside_rects.Add(right_bottom_rect);
      }     
    }

    Rect left_bottom_rect(rect.center + FVector2D(-texWidth, texLength), texWidth, texLength);
    status = IsPolygonInPolygon(left_bottom_rect.points(), corner_vertices);
    if (status != -1 ) {
      if (!contain_rect(inside_rects, left_bottom_rect)) {
        rects.Add(left_bottom_rect);
        inside_rects.Add(left_bottom_rect);
      }      
    }

  }

  for (int i = 0; i < inside_rects.Num();i++) {
    Rect rect = inside_rects[i];
    TArray<FVector2D> points = rect.points();
    vertices.Append(points);
  }
  return vertices;
}

int SampleComputeUVTileNum(const TArray<FVector2D>& polygon, float texWidth, float texHeight) {
  TArray<FVector2D> bounding_rect = GetBoundingRect(polygon);
  float height = FVector2D::Distance(bounding_rect[0], bounding_rect[1]);
  float width = FVector2D::Distance(bounding_rect[0], bounding_rect[3]);
  int u_num = width / texWidth;
  u_num = (u_num == (width / texWidth)) ? u_num : (u_num + 1);
  int v_num = height / texHeight;
  v_num = (v_num == (height / texHeight)) ? v_num : (v_num + 1);
  int tile_num = u_num > v_num ? u_num : v_num;
  return tile_num;
}

TArray<FVector2D> GetUVRect(const TArray<FVector2D>& polygon, float texWidth, float texHeight) {
  TArray<FVector2D> bounding_rect = GetBoundingRect(polygon);
  int tile_num = SampleComputeUVTileNum(polygon, texWidth, texHeight);
  TArray<FVector2D> uv_rect;
  uv_rect.Add(bounding_rect[0]);
  uv_rect.Add(bounding_rect[0] + tile_num*FVector2D(0, -texHeight));
  uv_rect.Add(bounding_rect[0] + tile_num*FVector2D(texWidth, -texHeight));
  uv_rect.Add(bounding_rect[0] + tile_num*FVector2D(texWidth, 0));


  return uv_rect;
}

FVector2D ComputeUV(const TArray<FVector2D>& uvRect, FVector2D vertex) {
  FVector2D origin = uvRect[0];
  float width = FVector2D::Distance(uvRect[0], uvRect[3]);
  float height = FVector2D::Distance(uvRect[0], uvRect[1]);

  FVector2D offset = vertex - origin;
  FVector2D uv(abs(offset.X) / width, abs(offset.Y) / height);
  return uv;
}

void build_wall_vertical_face(TArray<FVector> vectors, TArray<OpeningData*>& openings, 
  ProceduralMeshData& data, float texWidth, float texHeight) {
  FVector start_position = vectors[0];
  FVector end_position = vectors[1];
  FVector end_top_position = vectors[2];
  FVector start_top_position = vectors[3];

  FVector x_axis = end_position - start_position;
  x_axis.Normalize();

  FMatrix mat = compute_wall_matrix(start_position, end_position);
  FMatrix inverse_mat = mat.Inverse();

  TArray<FVector2D> vectors1;
  for (int i = 0; i < vectors.Num(); i++) {
    FVector vector = vectors[i];
    FVector4 vector4 = inverse_mat.TransformVector(vector);
    FVector2D vector2d(vector4.X, vector4.Z);
    vectors1.Add(vector2d);
  }

  TArray<FVector> vectors2;

  // transform opening vertex
  for (int i = 0; i < openings.Num(); i++) {
    OpeningData* openingData = openings[i];
    float length = openingData->length();
    float half_length = length / 2.0;
    FVector opening_vertex1 = openingData->position() + half_length*x_axis + FVector(0, 0, openingData->position().Z);
    vectors2.Add(opening_vertex1);
    FVector opening_vertex2 = openingData->position() - half_length*x_axis + FVector(0, 0, openingData->position().Z);
    vectors2.Add(opening_vertex2);
    FVector opening_vertex3 = opening_vertex2 + FVector(0, 0, openingData->height());
    vectors2.Add(opening_vertex3);
    FVector opening_vertex4 = opening_vertex1 + FVector(0, 0, openingData->height());
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
  bool bused_tex = true;
  if (texWidth <= 0 || texHeight <= 0) {
    bused_tex = false;
  }

  // compute uv
  if (bused_tex) {
    TArray<FVector2D> uv0s;
    TArray<FVector2D> uv_rect = GetUVRect(vectors1, texWidth, texHeight);
    for (int i = 0; i < face_points.Num(); i++) {
      FVector2D uv = ComputeUV(uv_rect, face_points[i]);
      uv0s.Add(uv);
    }
    data.uv0s = uv0s;
  }



  FVector4 tmp = inverse_mat.TransformVector(vectors[0]);
  TArray<FVector> vertices;
  for (int i = 0; i < face_points.Num(); i++) {
    FVector2D vector2d = face_points[i];
    FVector vector(vector2d.X, tmp.Y, vector2d.Y);
    FVector4 vector4 = mat.TransformVector(vector);
    FVector vertex = FVector(vector4.X, vector4.Y, vector4.Z);
    vertices.Add(vertex);
  }
  data.vertices = vertices;

  //FVector normal(-tmp.Y, tmp.X, 0);
  FVector tmp1 = end_position - start_position;
  FVector normal(-tmp1.Y, tmp1.X, 0);
  TArray<FVector> normals;
  for (int i = 0; i < face_points.Num(); i++) {
    normals.Add(normal);
  }
  data.normals = normals;

  TArray<int32> triangles;
  int face_num = face_points.Num() / 4;
  for (int i = 0; i < face_num; i++) {
    /*triangles.Add(0 + 4 * i);
    triangles.Add(2 + 4 * i);
    triangles.Add(1 + 4 * i);

    triangles.Add(0 + 4 * i);
    triangles.Add(3 + 4 * i);
    triangles.Add(2 + 4 * i);*/

    triangles.Add(1 + 4 * i);
    triangles.Add(2 + 4 * i);
    triangles.Add(0 + 4 * i);

    triangles.Add(2 + 4 * i);
    triangles.Add(3 + 4 * i);
    triangles.Add(0 + 4 * i);
  }
  data.triangles = triangles;
}

FMatrix compute_wall_matrix(FVector start_position, FVector end_position) {
  FVector x_axis = end_position - start_position;
  FVector z_axis(0, 0, 1);
  FVector y_axis = FVector::CrossProduct(z_axis, x_axis);
  y_axis = -y_axis;
  x_axis.Normalize();
  y_axis.Normalize();
  z_axis.Normalize();
  FVector w_axis = FVector::ZeroVector;
  FMatrix mat(x_axis, y_axis, z_axis, w_axis);
  return mat;
}

TArray<FVector2D> split_face(TArray<FVector2D>& face, TArray<FVector2D>& openings) {
  TArray<FVector2D> face_points;
  if (openings.Num() == 0) {
    face_points = face;
    return face_points;
  }

  TArray<float> x_tokens, y_tokens;

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
      FVector2D vec3(x_token, y_token);
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

TArray<FVector> compute_opening_vertex(FVector start_position, 
  FVector end_position,  OpeningData* openingData, const FMatrix& mat) {

  FVector x_axis = end_position - start_position;
  x_axis.Normalize();
  float length = openingData->length();
  float half_length = length / 2.0;

  TArray<FVector> vectors2;
  FVector opening_vertex1 = openingData->position() + half_length*x_axis + FVector(0, 0, openingData->position().Z);
  vectors2.Add(opening_vertex1);
  FVector opening_vertex2 = openingData->position() - half_length*x_axis + FVector(0, 0, openingData->position().Z);
  vectors2.Add(opening_vertex2);
  FVector opening_vertex3 = opening_vertex2 + FVector(0, 0, openingData->height());
  vectors2.Add(opening_vertex3);
  FVector opening_vertex4 = opening_vertex1 + FVector(0, 0, openingData->height());
  vectors2.Add(opening_vertex4);

  FVector4 tmp = mat.TransformVector(start_position);
  TArray<FVector> vectors3;
  for (int i = 0; i < vectors2.Num(); i++) {
    FVector vector = vectors2[i];
    FVector4 tmp_vector4 = mat.TransformVector(vector);
    FVector tmp_vector(tmp_vector4.X, tmp.Y, tmp_vector4.Z);
    FMatrix inverse_mat = mat.Inverse();
    FVector4 vector4 = inverse_mat.TransformVector(tmp_vector);
    FVector vertex(vector4.X, vector4.Y, vector4.Z);
    vectors3.Add(vertex);
  }
  return vectors3;
}

UStaticMesh* GetStaticMesh(UProceduralMeshComponent* ProcMeshComp,FString meshName) {
  FRawMesh RawMesh;
  TArray<UMaterialInterface*> MeshMaterials;
  const int32 NumSections = ProcMeshComp->GetNumSections();
  int32 VertexBase = 0;

  for (int32 SectionIdx = 0; SectionIdx < NumSections; SectionIdx++)
  {
    FProcMeshSection* ProcSection = ProcMeshComp->GetProcMeshSection(SectionIdx);

    // Copy verts
    for (FProcMeshVertex& Vert : ProcSection->ProcVertexBuffer)
    {
      RawMesh.VertexPositions.Add(Vert.Position);
    }

    // Copy 'wedge' info
    int32 NumIndices = ProcSection->ProcIndexBuffer.Num();
    for (int32 IndexIdx = 0; IndexIdx < NumIndices; IndexIdx++)
    {
      int32 Index = ProcSection->ProcIndexBuffer[IndexIdx];

      RawMesh.WedgeIndices.Add(Index + VertexBase);

      FProcMeshVertex& ProcVertex = ProcSection->ProcVertexBuffer[Index];

      FVector TangentX = ProcVertex.Tangent.TangentX;
      FVector TangentZ = ProcVertex.Normal;
      FVector TangentY = (TangentX ^ TangentZ).GetSafeNormal() * (ProcVertex.Tangent.bFlipTangentY ? -1.f : 1.f);

      RawMesh.WedgeTangentX.Add(TangentX);
      RawMesh.WedgeTangentY.Add(TangentY);
      RawMesh.WedgeTangentZ.Add(TangentZ);

      RawMesh.WedgeTexCoords[0].Add(ProcVertex.UV0);
      RawMesh.WedgeColors.Add(ProcVertex.Color);
    }

    // copy face info
    int32 NumTris = NumIndices / 3;
    for (int32 TriIdx = 0; TriIdx < NumTris; TriIdx++)
    {
      RawMesh.FaceMaterialIndices.Add(SectionIdx);
      RawMesh.FaceSmoothingMasks.Add(0); // Assume this is ignored as bRecomputeNormals is false
    }

    // Remember material
    MeshMaterials.Add(ProcMeshComp->GetMaterial(SectionIdx));

    // Update offset for creating one big index/vertex buffer
    VertexBase += ProcSection->ProcVertexBuffer.Num();
  }

  if (RawMesh.VertexPositions.Num() > 3 && RawMesh.WedgeIndices.Num() > 3) {
    //UWallMeshComponent* wall_component = ConstructObject<UWallMeshComponent>(UWallMeshComponent::StaticClass(), (UObject*)GetTransientPackage(), TEXT("my_wall"));
    UStaticMesh* StaticMesh = NewObject<UStaticMesh>((UObject*)GetTransientPackage(), FName(*meshName), RF_Public | RF_Standalone);
    StaticMesh->InitResources();
    StaticMesh->LightingGuid = FGuid::NewGuid();

    FStaticMeshSourceModel* SrcModel = new (StaticMesh->SourceModels) FStaticMeshSourceModel();
    SrcModel->BuildSettings.bRecomputeNormals = false;
    SrcModel->BuildSettings.bRecomputeTangents = false;
    SrcModel->BuildSettings.bRemoveDegenerates = false;
    SrcModel->BuildSettings.bUseHighPrecisionTangentBasis = false;
    SrcModel->BuildSettings.bUseFullPrecisionUVs = false;
    SrcModel->BuildSettings.bGenerateLightmapUVs = true;
    SrcModel->BuildSettings.SrcLightmapIndex = 0;
    SrcModel->BuildSettings.DstLightmapIndex = 1;
    SrcModel->RawMeshBulkData->SaveRawMesh(RawMesh);

    for (UMaterialInterface* Material : MeshMaterials)
    {
      StaticMesh->Materials.Add(Material);
    }

    // Build mesh from source
    StaticMesh->Build(false);
    return StaticMesh;
  }
  return NULL;
}