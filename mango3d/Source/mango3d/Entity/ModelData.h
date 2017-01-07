#pragma once

#include "BaseGeometryData.h"

class MANGO3D_API ModelData :public BaseGeometryData {

public:
  ModelData();
  ~ModelData();
  int model_type();
  FString model_name();
  virtual void InitWithJsonObject(FJsonObject& jsonObject);
protected:
  int model_type_;
  FString model_name_;
};
