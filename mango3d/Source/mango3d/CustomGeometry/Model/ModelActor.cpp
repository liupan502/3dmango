// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "ModelActor.h"

AModelActor::AModelActor() {
  model_data_ = NULL;
}

void AModelActor::InitWithModelData(ModelData* modelData) {
  model_data_ = modelData;
  init_static_mesh(modelData);
}

void AModelActor::init_static_mesh(ModelData* modelData) {

}


