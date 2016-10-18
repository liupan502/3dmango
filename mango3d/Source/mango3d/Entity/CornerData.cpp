#include "mango3d.h"
#include "CornerData.h"
#include "PointData.h"
#include "WallData.h"
#include <string>
#include <iostream>
#include <map>


CornerData::CornerData() :BaseGeometryData() {

}

CornerData::~CornerData() {
  ;
}

void CornerData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseGeometryData::InitWithJsonObject(jsonObject);
 
  related_wall_map_.clear();
  TArray<FString> wall_name_array;
  if (jsonObject.TryGetStringArrayField("wall_names", wall_name_array)) {
    for (int i = 0; i < wall_name_array.Num(); i++) {
      FString wall_name = wall_name_array[i];
      WallData* wall_data = new WallData();
      wall_data->set_name(wall_name);      
      related_wall_map_.insert(std::make_pair(wall_name, wall_data));      
    }
  }

  point_data_map_.clear();
  const TArray<TSharedPtr<FJsonValue>>* point_array ;
  if (jsonObject.TryGetArrayField("points", point_array)) {

    for (int i = 0; i < point_array->Num(); i++) {      
      FJsonValue* value = (*point_array)[i].Get();
      const TSharedPtr<FJsonObject>* object = NULL;
      value->TryGetObject(object);
      PointData* point_data = new PointData();
      point_data->InitWithJsonObject(*object->Get());
      point_data_map_.insert(std::make_pair(point_data->name(), point_data));
    }
  }

  FString generated_point_name;
  if (jsonObject.TryGetStringField("generated_point_name", generated_point_name)) {
    generated_point_ = point_data_map_[generated_point_name];
  }


}
