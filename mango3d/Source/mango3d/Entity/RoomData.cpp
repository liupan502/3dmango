#include "mango3d.h"
#include "RoomData.h"
#include "WallData.h"

RoomData::RoomData() :BaseData() {

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