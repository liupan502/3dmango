#ifndef MANGO_3D_CORNER_DATA_H_
#define MANGO_3D_CORNER_DATA_H_

#include "BaseData.h"
#include "BaseGeometryData.h"

class PointData;
class WallData;
class MANGO3D_API CornerData :public BaseGeometryData {
public:
  CornerData();
  ~CornerData();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);

protected:
  bool has_position_data_;
  std::map<FString, PointData*> point_data_map_;
  std::map<FString, WallData*> related_wall_map_;
  PointData* generated_point_;
};
#endif 
