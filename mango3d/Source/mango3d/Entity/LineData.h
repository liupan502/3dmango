#ifndef MANGO_3D_LINE_DATA_H_
#define MANGO_3D_LINE_DATA_H_
#include "BaseData.h"

class MANGO3D_API LineData :public BaseData {
public:
  LineData();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
  virtual ~LineData();

  FString start_point_name();
  void set_start_point_name(FString name);

  FString end_point_name();
  void set_end_point_name(FString name);

  bool is_independent();
  void set_is_independent(bool is_independent);

  FVector start_point_position();
  void set_start_point_position(FVector position);

  FVector end_point_position();
  void set_end_point_position(FVector position);
protected:
  FString start_point_name_;
  FString end_point_name_;
  bool is_independent_;
  FVector start_point_position_;
  FVector end_point_position_;

};
#endif
