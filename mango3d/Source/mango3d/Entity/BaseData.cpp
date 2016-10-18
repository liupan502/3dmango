// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "BaseData.h"

BaseData::BaseData()
{
}

BaseData::~BaseData()
{
}

void BaseData::InitWithJsonObject(FJsonObject& jsonObject) {
  FString name_str;  
  if (jsonObject.TryGetStringField("name", name_str)) {
    set_name(name_str);
  }
  else {
    set_name("");
  }
}

void BaseData::set_name(FString name) {
  name_ = name;
}

FString BaseData::name() const {
  return name_;
}
