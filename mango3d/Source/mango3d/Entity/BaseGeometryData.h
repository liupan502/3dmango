#ifndef MANGO_3D_BASE_GEOMETRY_DATA_H_
#define MANGO_3D_BASE_GEOMETRY_DATA_H_
#include "BaseData.h"

class MANGO3D_API BaseGeometryData :public BaseData {
public:
  BaseGeometryData();
  virtual ~BaseGeometryData();

  void set_length(float length);
  float length();

  void set_width(float width);
  float width();

  void set_height(float height);
  float height();

  void set_rotation_z(float rotationZ);
  float rotation_z();

  void set_rotation_x(float rotationX);
  float rotation_x();

  void set_rotation_y(float rotationY);
  float rotation_y();

  void set_position(FVector position);
  FVector position();

  virtual void InitWithJsonObject(FJsonObject& jsonObject);

protected:
  float length_;
  float width_;
  float height_;

  float rotation_x_;
  float rotation_y_;
  float rotation_z_;

  FVector position_;
};
#endif
