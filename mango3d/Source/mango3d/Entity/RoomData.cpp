#include "mango3d.h"
#include "RoomData.h"
#include "WallData.h"

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