#pragma once

#include "BaseGeometryData.h"

class MANGO3D_API ModelData :public BaseGeometryData {

public:
  ModelData();
  ~ModelData();

  virtual void InitWithJsonObject(FJsonObject& jsonObject);
protected:
  int model_type_;
  FString model_name_;
};
