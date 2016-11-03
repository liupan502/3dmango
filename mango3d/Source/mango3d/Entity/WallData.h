#ifndef MANGO_3D_WALL_DATA_H_
#define MANGO_3D_WALL_DATA_H_
#include "BaseData.h"
#include <set>

typedef enum WALL_DATA_TYPE {
  WALL_NO_DATA,

  // 存储数据为内墙线的数据
  WALL_INSIDE_DATA,

  // 存储的数据为墙中线数据
  WALL_MIDDLE_DATA,

  // 存储的数据为外墙线数据
  WALL_OUTSIDE_DATA,
} WALL_DATA_TYPE;

typedef enum WALL_DATA_STATUS {
  NONE_STAUS_WALL_DATA,
  DRAWING_WALL_DATA,
  UNROOM_WALL_DATA,
  ROOM_WALL_DATA,
} WALL_DATA_STATUS;


class CornerData;
class OpeningData;
class LineData;
class MANGO3D_API WallData : public BaseData {
public:
  WallData();
  virtual ~WallData();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
  void UpdateInitData(std::map<FString, CornerData*>& cornerDataMap);
  CornerData* GetConnectedCorner(const WallData* otherWall);
  bool IsStartCorner(const CornerData* corner)const;
  bool IsEndCorner(const CornerData* corner)const;
  bool DoCotainCorner(const CornerData* corner)const;
  std::set<FString> opening_names();

  CornerData* start_corner()const;
  CornerData* end_corner()const;

  FVector StartCornerPosition()const;
  FVector StartOutsidePosition()const;
  FVector StartInsidePosition()const;
  
  FVector EndCornerPosition()const;
  FVector EndOutsidePosition()const;
  FVector EndInsidePosition()const;



  //WALL_DATA_TYPE data_type();
  //WALL_DATA_STATUS status();
  

protected:
  WALL_DATA_TYPE data_type_;
  WALL_DATA_STATUS status_;
  LineData* line_;
  LineData* generated_line_;
  CornerData* start_corner_;
  CornerData* end_corner_;
  FVector normal_vector_;
  std::set<FString> opening_names_;
};
#endif
