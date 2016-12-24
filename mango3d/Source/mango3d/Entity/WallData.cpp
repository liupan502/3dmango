#include "mango3d.h"
#include "WallData.h"
#include "LineData.h"
#include "CornerData.h"
#include "Util/JsonUtil.h"

WallData::WallData() {
  data_type_ = WALL_NO_DATA;
  status_ = NONE_STAUS_WALL_DATA;
  line_ = NULL;
  generated_line_ = NULL;
  start_corner_ = NULL;
  end_corner_ = NULL;
}

WallData::~WallData() {
  if (line_ != NULL) {
    delete line_;
    line_ = NULL;
  }

  if (generated_line_ != NULL) {
    delete generated_line_;
    generated_line_ = NULL;
  }

  start_corner_ = NULL;
  end_corner_ = NULL;
}

void WallData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseGeometryData::InitWithJsonObject(jsonObject);

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

void WallData::UpdateInitData(std::map<FString, CornerData*>& cornerDataMap) {
  if (start_corner_ != NULL) {
    FString name = start_corner_->name();
    if (cornerDataMap.find(name) != cornerDataMap.end()) {
      CornerData* corner_data = cornerDataMap[name];
      if (corner_data != start_corner_) {
        delete start_corner_;
        start_corner_ = corner_data;
      }
    }
  }

  if (end_corner_ != NULL) {
    FString name = end_corner_->name();
    if (cornerDataMap.find(name) != cornerDataMap.end()) {
      CornerData* corner_data = cornerDataMap[name];
      if (corner_data != end_corner_) {
        delete end_corner_;
        end_corner_ = corner_data;
      }
    }
  }
}

CornerData* WallData::start_corner() const{
  return start_corner_;
}

CornerData* WallData::end_corner() const {
  return end_corner_;
}

FVector WallData::StartCornerPosition() const {
  return start_corner_->position();
}
FVector WallData::StartOutsidePosition() const {
  FString start_outside_name = generated_line_->start_point_name();
  FVector position = start_corner_->PointPosition(start_outside_name);
  return position;
}
FVector WallData::StartInsidePosition()const {
  FString start_inside_name = line_->start_point_name();
  FVector position = start_corner_->PointPosition(start_inside_name);
  return position;
}

FVector WallData::EndCornerPosition() const {
  return end_corner_->position();
}
FVector WallData::EndOutsidePosition() const {
  FString end_outside_name = generated_line_->end_point_name();
  FVector position = end_corner_->PointPosition(end_outside_name);
  return position;
}
FVector WallData::EndInsidePosition() const {
  FString end_inside_name = line_->end_point_name();
  FVector position = end_corner_->PointPosition(end_inside_name);
  return position;
}

std::set<FString> WallData::opening_names() {
  return opening_names_;
}


bool WallData::IsStartCorner(const CornerData* corner)const {
  return (start_corner_ == corner);
}

bool WallData::IsEndCorner(const CornerData* corner) const{
  return (end_corner_ == corner);
}

bool WallData::DoCotainCorner(const CornerData* corner)const {
  return IsStartCorner(corner) || IsEndCorner(corner);
}
CornerData* WallData::GetConnectedCorner(const WallData* otherWall) {
  CornerData* result = NULL;
  if (otherWall == NULL) {
    return result;
  }
  if (otherWall->DoCotainCorner(start_corner_)) {
    result = start_corner_;
  }
  else if (otherWall->DoCotainCorner(end_corner_)) {
    result = end_corner_;
  }
  return result;
}

