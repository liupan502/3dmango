#include "mango3d.h"
#include "LineData.h"
#include "Util/JsonUtil.h"

LineData::LineData():BaseData() {

}

LineData::~LineData() {

}

void LineData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseData::InitWithJsonObject(jsonObject);

  FString start_point_name;
  if (jsonObject.TryGetStringField("start_point_name", start_point_name)) {
    set_start_point_name(start_point_name);
  }

  FString end_point_name;
  if (jsonObject.TryGetStringField("end_point_name", end_point_name)) {
    set_end_point_name(end_point_name);
  }

  bool is_independent;
  if (jsonObject.TryGetBoolField("is_independent", is_independent)) {
    set_is_independent(is_independent);
  }

  FString start_point_str;
  if (jsonObject.TryGetStringField("start_point_position", start_point_str)) {
    FVector start_point_position = StringToVector2(start_point_str);
    set_start_point_position(start_point_position);
  }

  FString end_point_str;
  if (jsonObject.TryGetStringField("end_point_position", end_point_str)) {
    FVector end_point_position = StringToVector2(end_point_str);
    set_end_point_position(end_point_position);
  }
}

FString LineData::start_point_name() {
  return start_point_name_;
}

void LineData::set_start_point_name(FString name) {
  start_point_name_ = name;
}

FString LineData::end_point_name() {
  return end_point_name_;
}

void LineData::set_end_point_name(FString name) {
  end_point_name_ = name;
}

bool LineData::is_independent() {
  return is_independent_;
}

void LineData::set_is_independent(bool isIndependent) {
  is_independent_ = isIndependent;
}

FVector LineData::start_point_position() {
  return start_point_position_;
}

void LineData::set_start_point_position(FVector position) {
  start_point_position_ = position;
}

FVector LineData::end_point_position() {
  return end_point_position_;
}

void LineData::set_end_point_position(FVector position) {
  end_point_position_ = position;
}

