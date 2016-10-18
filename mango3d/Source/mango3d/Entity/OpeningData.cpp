#include "mango3d.h"
#include "OpeningData.h"

OpeningData::OpeningData():BaseGeometryData(){

}

OpeningData::~OpeningData() {

}

void OpeningData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseGeometryData::InitWithJsonObject(jsonObject);
  int opening_type_num;
  if (jsonObject.TryGetNumberField("opening_type", opening_type_num)) {
    set_opening_type((OPENING_TYPE)(opening_type_num));
  }

  FString wall_name;
  if (jsonObject.TryGetStringField("wall_name", wall_name)) {
    set_wall_name(wall_name);
  }
}

OPENING_TYPE OpeningData::opening_type() {
  return opening_type_;
}

void OpeningData::set_opening_type(OPENING_TYPE opening_type) {
  opening_type_ = opening_type;
}

FString OpeningData::wall_name() {
  return wall_name_;
}

void OpeningData::set_wall_name(FString wall_name) {
  wall_name_ = wall_name;
}