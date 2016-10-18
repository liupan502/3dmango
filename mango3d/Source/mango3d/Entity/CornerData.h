#ifndef MANGO_3D_CORNER_DATA_H_
#define MANGO_3D_CORNER_DATA_H_

#include "BaseData.h"
#include "BaseGeometryData.h"

class PointData;
class WallData;
class MANGO3D_API CornerData :BaseGeometryData {
public:
  CornerData();
  ~CornerData();

protected:
  bool has_position_data_;
  std::map<std::string, PointData*> point_data_map_;
  std::map<std::string, WallData*> related_wall_map_;
};
#endif 
