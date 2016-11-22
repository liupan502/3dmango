#include "mango3d.h"
#include "RoomData.h"
#include "WallData.h"
#include "CornerData.h"

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