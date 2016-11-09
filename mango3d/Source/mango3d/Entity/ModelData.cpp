#include "mango3d.h"
#include "ModelData.h"


ModelData::ModelData() {

}

ModelData::~ModelData() {

}

void ModelData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseGeometryData::InitWithJsonObject(jsonObject);
  int tmp_model_type;
  if (jsonObject.TryGetNumberField("model_type", tmp_model_type)) {
    model_type_ = tmp_model_type;
  }

  FString tmp_model_name;
  if (jsonObject.TryGetStringField("model_name", tmp_model_name)) {
    model_name_ = tmp_model_name;
  }

}