#ifndef MANGO_3D_CEILING_DATA_H_
#define MANGO_3D_CEILING_DATA_H_
#include "BaseData.h"
#include "RoomData.h"

enum CEILING_TYPE {
  CEILING_NONE,
  CEILING_CROSS_SECTION,
};

enum CEILING_UNIT_TYPE {
  CEILING_UNIT_NONE,
  CEILING_UNIT_LINE,
};

class MANGO3D_API BaseCeilingUnit {
public:

  CEILING_UNIT_TYPE ceiling_unit_type();
  virtual float width();
  
  //virtual FJsonObject ToJson();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
protected:
  CEILING_UNIT_TYPE ceiling_unit_type_;
};

class MANGO3D_API LineCeilingUnit : public BaseCeilingUnit {
public:
  LineCeilingUnit(FVector startPoint = FVector(), FVector endPoint = FVector());
  //virtual FJsonObject ToJson();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
  virtual float width();
  
  FVector start_point();
  FVector end_point();
protected:
  FVector start_point_;
  FVector end_point_;
};

class MANGO3D_API BaseCeilingData :public BaseData {
public:
  CEILING_TYPE ceiling_type();
  //virtual FJsonObject ToJson();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
  FString room_name();
protected:
  CEILING_TYPE ceiling_type_;
  FString room_name_;
};

class MANGO3D_API CrossSectionCeilingData : public BaseCeilingData {
public:

  //virtual FJsonObject ToJson();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
  std::vector<BaseCeilingUnit*> ceiling_units();
protected:
  std::vector<BaseCeilingUnit*> ceiling_units_;
};


#endif
