#include "mango3d.h"
#include "PointData.h"
#include "Util/JsonUtil.h"

PointData::PointData() :BaseData() {
  is_generated_ = false;
  has_point_data_ = false;
}

PointData::~PointData() {

}

void PointData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseData::InitWithJsonObject(jsonObject);
  bool is_generated;
  if (jsonObject.TryGetBoolField("is_generated", is_generated)){
    set_is_generated(is_generated);
  }

  bool has_point_data;
  if (jsonObject.TryGetBoolField("has_point_data", has_point_data)) {
    set_has_point_data(has_point_data);
  }

  FString point_str;
  if (jsonObject.TryGetStringField("point", point_str)) {
    FVector point = StringToVector2(point_str);
    set_point(point);
  }

}

FVector PointData::point() {
  return point_;
}

void PointData::set_point(FVector point) {
  point_ = point;
}

bool PointData::is_generated() {
  return is_generated_;
}

void PointData::set_is_generated(bool is_generated) {
  is_generated_ = is_generated;
}

bool PointData::has_point_data(){
  return has_point_data_;
}

void PointData::set_has_point_data(bool has_point_data) {
  has_point_data_ = has_point_data;
}