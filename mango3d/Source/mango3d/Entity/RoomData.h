#ifndef MANGO_3D_ROOM_DATA_H_
#define MANGO_3D_ROOM_DATA_H_

#include "BaseData.h"


class WallData;
class CornerData;
class PointData;
class MANGO3D_API RoomData :public BaseData {
public:
  RoomData();
  virtual ~RoomData();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
  void UpdateInitData(std::map<FString,WallData*>& wallDataMap);
  std::vector<CornerData*> GetCorners()const;
  const std::vector<WallData*> GetWalls() const ;
  TArray<FVector2D> GetCornerPositions()const;
  bool DoCotainWall(const WallData* wallData) const;
  TArray<FVector> InnerWallPoints();

protected:
  FString func_name_;
  std::vector<WallData*> walls_;
  TArray<FString> ceiling_names_;
};
#endif
