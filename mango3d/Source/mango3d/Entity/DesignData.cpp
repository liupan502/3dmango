#include "mango3d.h"
#include "DesignData.h"
#include "RoomData.h"
#include "CornerData.h"
#include "WallData.h"
#include "OpeningData.h"
#include "ModelData.h"

DesignData::DesignData() :BaseData()
{
}

DesignData::~DesignData()
{
  std::map<FString, WallData*>::iterator wall_it = wall_data_map_.begin();
  for (; wall_it != wall_data_map_.end(); wall_it++) {
    delete wall_it->second;
    wall_it->second = NULL;
  }

  std::map<FString, CornerData*>::iterator corner_it = corner_data_map_.begin();
  for (; corner_it != corner_data_map_.end(); corner_it++) {
    delete corner_it->second;
    corner_it->second = NULL;
  }

  std::map<FString, RoomData*>::iterator room_it = room_data_map_.begin();
  for (; room_it != room_data_map_.end(); room_it++) {
    delete room_it->second;
    room_it->second = NULL;
  }
}

void DesignData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseData::InitWithJsonObject(jsonObject);

  wall_data_map_.clear();
  const TArray<TSharedPtr<FJsonValue>>* wall_data_array;
  if (jsonObject.TryGetArrayField("walls",wall_data_array)) {
    for (int i = 0; i < wall_data_array->Num(); i++) {
      FJsonValue* wall_data_value = (*wall_data_array)[i].Get();
      const TSharedPtr<FJsonObject>* wall_data_share_object;
      wall_data_value->TryGetObject(wall_data_share_object);
      FJsonObject* wall_data_object = wall_data_share_object->Get();
      WallData* wall_data = new WallData();
      wall_data->InitWithJsonObject(*wall_data_object);
      wall_data_map_.insert(std::make_pair(wall_data->name(), wall_data));
    }
  }

  corner_data_map_.clear();
  const TArray<TSharedPtr<FJsonValue>>* corner_data_array;
  if (jsonObject.TryGetArrayField("corners", corner_data_array)) {
    for (int i = 0; i < corner_data_array->Num(); i++) {
      FJsonValue* corner_data_value = (*corner_data_array)[i].Get();
      const TSharedPtr<FJsonObject>* corner_data_share_object;
      corner_data_value->TryGetObject(corner_data_share_object);
      FJsonObject* corner_data_object = corner_data_share_object->Get();
      CornerData* corner_data = new CornerData();
      corner_data->InitWithJsonObject(*corner_data_object);
      corner_data_map_.insert(std::make_pair(corner_data->name(), corner_data));
    }
  }

  opening_data_map_.clear();
  const TArray<TSharedPtr<FJsonValue>>*  opening_data_array;
  if (jsonObject.TryGetArrayField("openings", opening_data_array)) {
    for (int i = 0; i < opening_data_array->Num(); i++) {
      FJsonValue* opening_data_value = (*opening_data_array)[i].Get();
      const TSharedPtr<FJsonObject>* opening_data_share_object;
      opening_data_value->TryGetObject(opening_data_share_object);
      FJsonObject* opening_data_object = opening_data_share_object->Get();
      OpeningData* opening_data = new OpeningData();
      opening_data->InitWithJsonObject(*opening_data_object);
      opening_data_map_.insert(std::make_pair(opening_data->name(), opening_data));
    }
  }

  room_data_map_.clear();
  const TArray<TSharedPtr<FJsonValue>>* room_data_array;
  if (jsonObject.TryGetArrayField("rooms", room_data_array)) {
    for (int i = 0; i < room_data_array->Num(); i++) {
      FJsonValue* room_data_value = (*room_data_array)[i].Get();
      const TSharedPtr<FJsonObject>* room_data_share_object;
      room_data_value->TryGetObject(room_data_share_object);
      FJsonObject* room_data_object = room_data_share_object->Get();
      RoomData* room_data = new RoomData();
      room_data->InitWithJsonObject(*room_data_object);
      room_data_map_.insert(std::make_pair(room_data->name(), room_data));

    }
  }

  model_data_map_.clear();
  const TArray<TSharedPtr<FJsonValue>>* model_data_array;
  if (jsonObject.TryGetArrayField("models", model_data_array)) {
    for (int i = 0; i < model_data_array->Num(); i++) {
      FJsonValue* model_data_value = (*model_data_array)[i].Get();
      const TSharedPtr<FJsonObject>* model_data_share_object;
      model_data_value->TryGetObject(model_data_share_object);
      FJsonObject* model_data_object = model_data_share_object->Get();
      ModelData* model_data = new ModelData();
      model_data->InitWithJsonObject(*model_data_object);
      model_data_map_.insert(std::make_pair(model_data->name(),model_data));
    }
  }

  update_init_data();
}

void DesignData::update_init_data() {
  std::map<FString, WallData*>::iterator wall_it = wall_data_map_.begin();
  for (; wall_it != wall_data_map_.end(); wall_it++) {
    wall_it->second->UpdateInitData(corner_data_map_);
  }

  std::map<FString, CornerData*>::iterator corner_it = corner_data_map_.begin();
  for (; corner_it != corner_data_map_.end(); corner_it++) {
    corner_it->second->UpdateInitData(wall_data_map_);
  }

  std::map<FString, RoomData*>::iterator room_it = room_data_map_.begin();
  for (; room_it != room_data_map_.end(); room_it++) {
    room_it->second->UpdateInitData(wall_data_map_);
  }
}

TArray<WallData*> DesignData::GetWalls() {
  TArray<WallData*> walls;
  std::map<FString, WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    walls.Add(it->second);
  }
  return walls;
}

TArray<RoomData*> DesignData::GetRooms() {
  TArray<RoomData*> rooms;
  std::map<FString, RoomData*>::iterator it;
  for (it = room_data_map_.begin(); it != room_data_map_.end(); it++) {
    rooms.Add(it->second);
  }
  return rooms;
}

TArray<OpeningData*> DesignData::GetRelatedOpenings(WallData* wall) {
  TArray<OpeningData*> openings;
  std::set<FString> opening_names = wall->opening_names();
  std::set<FString>::iterator it;
  for (it = opening_names.begin(); it != opening_names.end(); it++) {
    OpeningData* opening_data = opening_data_map_[*it];
    openings.Add(opening_data);
  }
  return openings;
}

std::map<FString, OpeningData*> DesignData::opening_data_map() {
  return opening_data_map_;
}

TArray<WallData*> DesignData::GetOutsideWalls(){
  TArray<WallData*> tmp_walls;
  for (std::map<FString, WallData*>::iterator it = wall_data_map_.begin();
    it != wall_data_map_.end(); it++) {
    WallData* wall_data = it->second;
    int ref_room_num = 0;
    for (std::map<FString, RoomData*>::iterator it = room_data_map_.begin();
      it != room_data_map_.end(); it++) {
      if (it->second->DoCotainWall(wall_data))
        ref_room_num++;
    }
    if (ref_room_num == 1) {
      tmp_walls.Add(wall_data);
    }
  }

  // 重亲排列wall ，使墙之间首尾相连
  TArray<WallData*> outside_walls;
  WallData* current_wall = NULL;
  while (true) {
    bool bfind_next_wall = false;
    for (int i = 0; i < tmp_walls.Num(); i++) {
      WallData* tmp_wall = tmp_walls[i];
      bool is_next_wall = false;
      if (current_wall == NULL) {
        is_next_wall = true;
      }
      else if(current_wall->DoCotainCorner(tmp_wall->start_corner()) ||
        current_wall->DoCotainCorner(tmp_wall->end_corner())){
        is_next_wall = true;
      }

      if (is_next_wall) {
        bfind_next_wall = true;
        tmp_walls.RemoveAt(i);
        outside_walls.Add(tmp_wall);
        current_wall = tmp_wall;
      }
    }

    if (!bfind_next_wall)
      break;
  }
  return outside_walls;
}

TArray<ModelData*> DesignData::GetModels() {
  TArray<ModelData*> models;
  for (std::map<FString, ModelData*>::iterator it = model_data_map_.begin();
    it != model_data_map_.end(); it++) {
    models.Add(it->second);
  }
  return models;
}