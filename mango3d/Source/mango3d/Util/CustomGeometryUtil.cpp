#include "mango3d.h"
#include "CustomGeometryUtil.h"
#include "Entity/RoomData.h"
#include "Entity/CornerData.h"
#include "Entity/WallData.h"
#include "PolygonUtil.h"
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
  TArray<FVector2D> corner_vertices = GetRoomDataCornerPositions(roomData);
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

int is_polygon_in_polygon(const TArray<FVector2D>& polygon1, const TArray<FVector2D>& polygon2) {
  int num = 0;
  for (int i = 0; i < polygon1.Num(); i++) {
    FVector2D point = polygon1[i];
    if (IsPointInPolygon(point, polygon2)) {
      num++;
    }
  }

  // 完全不包含
  if (num == 0) {
    return -1;
  }

  // 不完全包含
  if (num < polygon1.Num()) {
    return 0;
  }

  // 完全包含
  return 1;
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
  //generate_room_mesh(corner_vertices, vertices);
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
      status = is_polygon_in_polygon(rect.points(), corner_vertices);
      if (status != -1) {
        inside_rects.Add(rect);
      }
    }
    
    Rect top_rect(rect.center+FVector2D(0,-texLength),texWidth, texLength);
    status = is_polygon_in_polygon(top_rect.points(), corner_vertices);
    if (status != -1) {  
      if (!contain_rect(inside_rects,top_rect)) {
        rects.Add(top_rect);
        inside_rects.Add(top_rect);
      }     
    }

    Rect left_rect(rect.center + FVector2D(-texWidth, 0), texWidth, texLength);
    status = is_polygon_in_polygon(left_rect.points(), corner_vertices);
    if (status != -1 ) {
      if (!contain_rect(inside_rects, left_rect)) {
        rects.Add(left_rect);
        inside_rects.Add(left_rect);
      }      
    }

    Rect right_rect(rect.center + FVector2D(texWidth, 0), texWidth, texLength);
    status = is_polygon_in_polygon(right_rect.points(), corner_vertices);
    if (status != -1) {
      if (!contain_rect(inside_rects, right_rect)) {
        rects.Add(right_rect);
        inside_rects.Add(right_rect);
      }      
    }

    Rect bottom_rect(rect.center + FVector2D(0, texLength), texWidth, texLength);
    status = is_polygon_in_polygon(bottom_rect.points(), corner_vertices);
    if (status != -1) {
      if (!contain_rect(inside_rects, bottom_rect)) {
        rects.Add(bottom_rect);
        inside_rects.Add(bottom_rect);
      }      
    }
    
    Rect left_top_rect(rect.center + FVector2D(-texWidth, -texLength), texWidth, texLength);
    status = is_polygon_in_polygon(left_top_rect.points(), corner_vertices);
    if (status != -1) {
      if (!contain_rect(inside_rects, left_top_rect)) {
        rects.Add(left_top_rect);
        inside_rects.Add(left_top_rect);
      }
    }

    Rect right_top_rect(rect.center + FVector2D(texWidth, -texLength), texWidth, texLength);
    status = is_polygon_in_polygon(right_top_rect.points(), corner_vertices);
    if (status != -1) {
      if (!contain_rect(inside_rects, right_top_rect)) {
        rects.Add(right_top_rect);
        inside_rects.Add(right_top_rect);
      }      
    }

    Rect right_bottom_rect(rect.center + FVector2D(texWidth, texLength), texWidth, texLength);
    status = is_polygon_in_polygon(right_bottom_rect.points(), corner_vertices);
    if (status != -1 ) {
      if (!contain_rect(inside_rects, right_bottom_rect)) {
        rects.Add(right_bottom_rect);
        inside_rects.Add(right_bottom_rect);
      }     
    }

    Rect left_bottom_rect(rect.center + FVector2D(-texWidth, texLength), texWidth, texLength);
    status = is_polygon_in_polygon(left_bottom_rect.points(), corner_vertices);
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