#include "mango3d.h"
#include "DesignData.h"
#include "RoomData.h"
#include "CornerData.h"
#include "WallData.h"
#include "OpeningData.h"

DesignData::DesignData() :BaseData()
{
}

DesignData::~DesignData()
{
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
}