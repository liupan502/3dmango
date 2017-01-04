#include "mango3d.h"
#include "CeilingData.h"
#include "Util/JsonUtil.h"



BaseCeilingUnit* CreateCeilingUnit(FJsonObject& jsonObject) {
  BaseCeilingUnit* ceiling_unit = NULL;
  CEILING_UNIT_TYPE type = CEILING_UNIT_NONE;
  uint32 tmp;
  if (jsonObject.TryGetNumberField("ceiling_unit_type", tmp)) {
    type = (CEILING_UNIT_TYPE)tmp;
  } 

  switch (type) {
  case CEILING_UNIT_LINE:
    ceiling_unit = (BaseCeilingUnit*)(new LineCeilingUnit());
    break;
  default:
    ceiling_unit = new BaseCeilingUnit();
    break;
  }
  ceiling_unit->InitWithJsonObject(jsonObject);
  return ceiling_unit;
}

CEILING_UNIT_TYPE BaseCeilingUnit::ceiling_unit_type() {
  return ceiling_unit_type_;
}

/*FJsonObject BaseCeilingUnit::ToJson() {
  FJsonObject object;
  object.insert("ceiling_type", QJsonValue((int)ceiling_unit_type()));
  return object;
}*/

void BaseCeilingUnit::InitWithJsonObject(FJsonObject& jsonObject) {
  uint32 tmp;
  if (jsonObject.TryGetNumberField("ceiling_type", tmp)) {
    ceiling_unit_type_ = (CEILING_UNIT_TYPE)tmp;
  }  
  else {
    ceiling_unit_type_ = CEILING_UNIT_NONE;
  }
}

LineCeilingUnit::LineCeilingUnit(FVector startPoint, FVector endPoint) {
  start_point_ = startPoint;
  end_point_ = endPoint;
  ceiling_unit_type_ = CEILING_UNIT_LINE;
}

FVector LineCeilingUnit::start_point() {
  return start_point_;
}

FVector LineCeilingUnit::end_point() {
  return end_point_;
}

/*QJsonObject LineCeilingUnit::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseCeilingUnit::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("start_point", QJsonValue(QVector2DToString(start_point())));
  object.insert("end_point", QJsonValue(QVector2DToString(end_point())));
  return object;
}*/

void LineCeilingUnit::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseCeilingUnit::InitWithJsonObject(jsonObject);
  FString tmp;
  if (jsonObject.TryGetStringField("start_point", tmp)) {    
    start_point_ = StringToVector2(tmp);
  }  
  else {
    start_point_ = FVector();
  }

  if (jsonObject.TryGetStringField("end_point", tmp)) {
    end_point_ = StringToVector2(tmp);
  }
  else {
    end_point_ = FVector();
  }
}

FString CeilingDataInstance::room_name() {
  return room_name_;
}

void CeilingDataInstance::set_room_name(const FString& room_name) {
  room_name_ = room_name;
}

CEILING_TYPE BaseCeilingData::ceiling_type() {
  return ceiling_type_;
}

/*QJsonObject BaseCeilingData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseData::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("ceiling_type", QJsonValue(ceiling_type()));
  return object;
}*/

void BaseCeilingData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseData::InitWithJsonObject(jsonObject);
  uint32 tmp;
  if (jsonObject.TryGetNumberField("ceiling_type", tmp)) {
    ceiling_type_ = (CEILING_TYPE)(tmp);
  } 
  else {
    ceiling_type_ = CEILING_NONE;
  }

  FString str_tmp;
  if (jsonObject.TryGetStringField("room_name", str_tmp)) {
    room_name_ = str_tmp;
  }
  else {
    room_name_ = "";
  }
  
}

/*QJsonObject CrossSectionCeilingData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseCeilingData::ToJson();
  AttachJsonObject(object, parent_object);
  //object.insert("ceiling_type", QJsonValue(ceiling_type()));
  QJsonArray ceiling_unit_jsons;
  for (int i = 0; i < ceiling_units.size(); i++) {
    QJsonObject unit_object = ceiling_units[i]->ToJson();
    ceiling_unit_jsons.append(QJsonValue(unit_object));
  }
  object.insert("ceiling_units", QJsonValue(ceiling_unit_jsons));
  return object;
}*/

FString BaseCeilingData::room_name() {
  return room_name_;
}

void CrossSectionCeilingData::InitWithJsonObject(FJsonObject& jsonObject) {
  BaseCeilingData::InitWithJsonObject(jsonObject);
  const TArray<TSharedPtr<FJsonValue>>* ceiling_unit_array;
  if (jsonObject.TryGetArrayField("ceiling_units", ceiling_unit_array)) {
    ceiling_units_.clear();
    for (int i = 0; i < ceiling_unit_array->Num(); i++) {
      FJsonValue* ceiling_unit_value = (*ceiling_unit_array)[i].Get();
      const TSharedPtr<FJsonObject>* ceiling_unit_share_object;
      ceiling_unit_value->TryGetObject(ceiling_unit_share_object);
      FJsonObject* ceiling_unit_object = ceiling_unit_share_object->Get();
      BaseCeilingUnit* base_ceiling_unit = CreateCeilingUnit(*ceiling_unit_object);
      base_ceiling_unit->InitWithJsonObject(*ceiling_unit_object);
      ceiling_units_.push_back(base_ceiling_unit);
    }    
  }
}



