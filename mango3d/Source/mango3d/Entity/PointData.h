#ifndef MANGO_3D_POINT_DATA_H_
#define MANGO_3D_POINT_DATA_H_
#include "BaseData.h"
class MANGO3D_API PointData :public BaseData {
public:
  PointData();
  virtual ~PointData();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
  

  FVector point();
  void set_point(FVector point);

  bool is_generated();
  void set_is_generated(bool is_generated);

  bool has_point_data();
  void set_has_point_data(bool has_point_data);

protected:
  FVector point_;
  bool is_generated_;
  bool has_point_data_;
};
#endif
