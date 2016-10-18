#ifndef MANGO_3D_OPENING_DATA_H_
#define MANGO_3D_OPENING_DATA_H_
#include "BaseData.h"
#include "BaseGeometryData.h"

typedef enum OPENING_TYPE {
  OPENING_NONE,
  OPENING_SINGLE_DOOR,
  OPENING_DOUBLE_DOOR,
  OPENING_MOVE_DOOR,
  OPENING_WINDOW,
} OPENING_TYPE;
class MANGO3D_API OpeningData :public BaseGeometryData {
public:
  OpeningData();
  virtual ~OpeningData();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);

  OPENING_TYPE opening_type();
  void set_opening_type(OPENING_TYPE opening_type);

  FString wall_name();
  void set_wall_name(FString wall_name);

protected:
  OPENING_TYPE opening_type_;
  FString wall_name_;
};
#endif
