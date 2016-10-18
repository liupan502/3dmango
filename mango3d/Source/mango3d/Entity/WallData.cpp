#include "mango3d.h"
#include "WallData.h"
#include "LineData.h"
#include "CornerData.h"
#include "Util/JsonUtil.h"

WallData::WallData() {

}

WallData::~WallData() {

}

void WallData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseData::InitWithJsonObject(jsonObject);

  int wall_data_type;
  if (jsonObject.TryGetNumberField("wall_data_type", wall_data_type)) {
    data_type_ = (WALL_DATA_TYPE)wall_data_type;
  }

  int wall_data_status;
  if (jsonObject.TryGetNumberField("wall_data_status", wall_data_status)) {
    status_ = (WALL_DATA_STATUS)wall_data_status;
  }

  const TSharedPtr<FJsonObject>* line_object;
  if (jsonObject.TryGetObjectField("line", line_object)) {
    LineData* line = new LineData();
    line->InitWithJsonObject(*line_object->Get());
    line_ = line;
  }

  const TSharedPtr<FJsonObject>* generated_line_object;
  if (jsonObject.TryGetObjectField("generated_line", generated_line_object)) {
    LineData* line = new LineData();
    line->InitWithJsonObject(*generated_line_object->Get());
    generated_line_ = line;
  }

  FString start_corner_name;
  if (jsonObject.TryGetStringField("start_corner_name", start_corner_name)) {
    CornerData* corner = new CornerData();
    corner->set_name(start_corner_name);
    start_corner_ = corner;
  }

  FString end_corner_name;
  if (jsonObject.TryGetStringField("end_corner_name", end_corner_name)) {
    CornerData* corner = new CornerData();
    corner->set_name(end_corner_name);
    end_corner_ = corner;
  }

  FString normal_vector_str;
  if (jsonObject.TryGetStringField("normal_vector", normal_vector_str)) {
    normal_vector_ = StringToVector2(normal_vector_str);
  }

  opening_names_.clear();
  TArray<FString> opening_name_array;
  if (jsonObject.TryGetStringArrayField("opening_names", opening_name_array)) {
    for (int i = 0; i < opening_name_array.Num(); i++) {
      FString opening_name = opening_name_array[i];
      opening_names_.insert(opening_name);
    }
  }
}