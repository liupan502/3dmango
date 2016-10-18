#include "mango3d.h"
#include "PointData.h"

PointData::PointData() :BaseData() {

}

PointData::~PointData() {

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