#ifndef MANGO_3D_DESIGN_DATA_H_
#define MANGO_3D_DESIGN_DATA_H_
#include "BaseData.h"

class WallData;
class CornerData;
class OpeningData;
class RoomData;

class MANGO3D_API DesignData :public BaseData
{
public:
  DesignData();
  virtual ~DesignData();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);

  TArray<WallData*> GetWalls();
  TArray<RoomData*> GetRooms();
  TArray<OpeningData*> GetRelatedOpenings(WallData* wall);


protected:
  std::map<FString, WallData*> wall_data_map_;

  std::map<FString, CornerData*> corner_data_map_;
  
  std::map<FString, RoomData*> room_data_map_;

  std::map<FString, OpeningData*> opening_data_map_;

  void update_init_data();
};

#endif
