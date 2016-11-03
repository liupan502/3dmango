#include "mango3d.h"
#include "CustomGeometryUtil.h"
#include "Entity/RoomData.h"
#include "Entity/CornerData.h"
#include "PolygonUtil.h"
#include <vector>

void CreateMeshSectionWithData(UProceduralMeshComponent* umc, int sectionIndex, ProceduralMeshData& data) {
  umc->CreateMeshSection(sectionIndex, data.vertices, data.triangles,
    data.normals, data.uv0s, data.vertex_colors,
    data.tangents, data.bool_value);
}

TArray<FVector2D> BuildRoomMesh(const RoomData* roomData) {
  std::vector<CornerData*> corners = roomData->GetCorners();
  TArray<FVector2D> corner_vertices;
  for (int i = 0; i < corners.size(); i++) {
    FVector tmp = corners[i]->position();
    FVector2D corner_vertex(tmp.X, tmp.Y);
    corner_vertices.Add(corner_vertex);
  }
  TArray<FVector2D> result = Triangulation(corner_vertices);
  return result;
}