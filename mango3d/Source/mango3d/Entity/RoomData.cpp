#include "mango3d.h"
#include "RoomData.h"
#include "WallData.h"
#include "CornerData.h"

#include "Util/PolygonUtil.h"

RoomData::RoomData() :BaseData() {
  func_name_ = "";

}

RoomData::~RoomData() {
  
}

void RoomData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseData::InitWithJsonObject(jsonObject);
  FString func_name;
  if (jsonObject.TryGetStringField("func_name", func_name)) {
    func_name_ = func_name;
  }

  walls_.clear();
  TArray<FString> wall_name_array;
  if (jsonObject.TryGetStringArrayField("wall_names", wall_name_array)) {
    for (int i = 0; i < wall_name_array.Num(); i++) {
      FString wall_name = wall_name_array[i];
      WallData* wall_data = new WallData();
      wall_data->set_name(wall_name);
      walls_.push_back(wall_data);
    }
  }

  //ceiling_names_.RemoveAll(Predicate;
  //TArray<FString> tmp_Array;
  if (jsonObject.TryGetStringArrayField("ceiling_names", ceiling_names_)) {

  }
}

void RoomData::UpdateInitData(std::map<FString, WallData*>& wallDataMap) {
  
  for (size_t i = 0; i<walls_.size(); i++) {
    WallData* wall_data = walls_[i];
    if (wallDataMap.find(wall_data->name()) != wallDataMap.end()) {
      if (wallDataMap[wall_data->name()] != wall_data) {
        walls_[i] = wallDataMap[wall_data->name()];
        delete wall_data;
        wall_data = NULL;
      }
    }
  }

}

std::vector<CornerData*> RoomData::GetCorners()const {
  std::vector<CornerData*> result;
  for (size_t i = 0; i < walls_.size(); i++) {
    int j = (i + 1) % walls_.size();
    WallData* wall1 = walls_[i];
    WallData* wall2 = walls_[j];
    CornerData* corner = wall1->GetConnectedCorner(wall2);
    result.push_back(corner);
  }
  return result;
}

const std::vector<WallData*> RoomData::GetWalls()const  {
  return walls_;
}

TArray<FVector2D> RoomData::GetCornerPositions() const {
  std::vector<CornerData*> corners = GetCorners();
  TArray<FVector2D> corner_vertices;
  for (size_t i = 0; i < corners.size(); i++) {
    FVector tmp = corners[i]->position();
    FVector2D corner_vertex(tmp.X, tmp.Y);
    corner_vertices.Add(corner_vertex);
  }
  return corner_vertices;
}

bool RoomData::DoCotainWall(const WallData* wallData) const {
  bool bcontain_wall = false;
  for (int i = 0; i < walls_.size(); i++) {
    if (walls_[i] == wallData) {
      bcontain_wall = true;
      break;
    }
  }
  return bcontain_wall;
}

TArray<FVector> RoomData::InnerWallPoints() {
  TArray<FVector> inner_wall_points;
  TArray<FVector2D> corner_positions = GetCornerPositions();
  bool is_clockwise = IsClockwisePolygon(corner_positions);

  for (int i = 0; i < walls_.size(); i++) {
    int j = (i + 1) % walls_.size();
    int k = (i + 2) % walls_.size();

    WallData* wall_data1 = walls_[i];
    WallData* wall_data2 = walls_[j];
    WallData* wall_data3 = walls_[k];

    CornerData* corner1 = wall_data1->GetConnectedCorner(wall_data2);
    FVector position1 = corner1->position();
    CornerData* corner2 = wall_data2->GetConnectedCorner(wall_data3);
    FVector position2 = corner2->position();
    
    FVector tmp = position2 - position1;
    FVector normal_vector = wall_data2->normal_vector();
    float value = tmp.X*normal_vector.Y - tmp.Y*normal_vector.X;
    if (is_clockwise) {
      value = value*-1;
    }

    // 选择line为内墙
    if (value < 0) {
      if (wall_data2->IsStartCorner(corner1)) {
        inner_wall_points.Add(wall_data2->StartInsidePosition());
      }
      else {
        inner_wall_points.Add(wall_data2->EndInsidePosition());
      }
    }
    // 选择generated-line 为内墙
    else {
      if (wall_data2->IsStartCorner(corner1)) {
        inner_wall_points.Add(wall_data2->StartOutsidePosition());
      }
      else {
        inner_wall_points.Add(wall_data2->EndOutsidePosition());
      }
    }

  }

  return inner_wall_points;
}