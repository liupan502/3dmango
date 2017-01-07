#ifndef MANGO_3D_DESIGN_DATA_H_
#define MANGO_3D_DESIGN_DATA_H_
#include "BaseData.h"

class WallData;
class CornerData;
class OpeningData;
class RoomData;
class ModelData;
class BaseCeilingData;
class CrossSectionCeilingData;

class MANGO3D_API DesignData :public BaseData
{
public:
  DesignData();
  virtual ~DesignData();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);

  TArray<WallData*> GetWalls();
  TArray<WallData*> GetOutsideWalls();
  TArray<RoomData*> GetRooms();
  TArray<ModelData*> GetModels();
  TArray<OpeningData*> GetRelatedOpenings(WallData* wall);
  TArray<CrossSectionCeilingData*> GetCrossSectionCeilingData();

  std::map<FString, OpeningData*> opening_data_map();

protected:
  std::map<FString, WallData*> wall_data_map_;

  std::map<FString, CornerData*> corner_data_map_;
  
  std::map<FString, RoomData*> room_data_map_;

  std::map<FString, OpeningData*> opening_data_map_;

  std::map<FString, ModelData*> model_data_map_;

  std::map<FString, BaseCeilingData*> ceiling_data_map_;

  void update_init_data();
};

#endif
