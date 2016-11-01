#include "mango3d.h"
#include "BaseGeometryData.h"
#include "Util/JsonUtil.h"

BaseGeometryData::BaseGeometryData() {
  width_ = length_ = height_ = 0.0;
  rotation_x_ = rotation_y_ = rotation_z_ = 0.0;
  set_position(FVector());
}

BaseGeometryData::~BaseGeometryData() {
  ;
}

void BaseGeometryData::set_length(float length) {
  length_ = length;
}

float BaseGeometryData::length() {
  return length_;
}

void BaseGeometryData::set_width(float width) {
  width_ = width;
}

float BaseGeometryData::width() {
  return width_;
}

void BaseGeometryData::set_height(float height) {
  height_ = height;
}

float BaseGeometryData::height() {
  return height_;
}

void BaseGeometryData::set_rotation_z(float rotationZ) {
  rotation_z_ = rotationZ;
}

float BaseGeometryData::rotation_z() {
  return rotation_z_;
}

void BaseGeometryData::set_rotation_x(float rotationX) {
  rotation_x_ = rotationX;
}

float BaseGeometryData::rotation_x() {
  return rotation_x_;
}

void BaseGeometryData::set_rotation_y(float rotationY) {
  rotation_y_ = rotationY;
}

float BaseGeometryData::rotation_y() {
  return rotation_y_;
}

void BaseGeometryData::set_position(FVector position) {
  position_ = position;
}

FVector BaseGeometryData::position(){
  return position_;
}

void BaseGeometryData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseData::InitWithJsonObject(jsonObject);
  double length_value;
  if (jsonObject.TryGetNumberField("length", length_value)) {
    set_length(length_value);
  }

  double width_value;
  if (jsonObject.TryGetNumberField("width", width_value)) {
    set_width(width_value);
  }

  double height_value;
  if (jsonObject.TryGetNumberField("height", height_value)) {
    set_height(height_value);
  }

  double rotation_x_value;
  if (jsonObject.TryGetNumberField("rotation_x", rotation_x_value)) {
    set_rotation_x(rotation_x_value);
  }

  double rotation_y_value;
  if (jsonObject.TryGetNumberField("rotation_y", rotation_y_value)) {
    set_rotation_y(rotation_y_value);
  }

  double rotation_z_value;
  if (jsonObject.TryGetNumberField("rotation_z", rotation_z_value)) {
    set_rotation_z(rotation_z_value);
  }

  FString position_str;
  if (jsonObject.TryGetStringField("position", position_str)) {
    FVector vector = StringToVector3(position_str);
    set_position(vector);
  }
}