// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "ModelActor.h"
#define _USE_MATH_DEFINES
#include <math.h>

AModelActor::AModelActor() {
  model_data_ = NULL;
}

void AModelActor::InitWithModelData(ModelData* modelData) {
  model_data_ = modelData;
  init_static_mesh(modelData);
}

void AModelActor::init_static_mesh(ModelData* modelData) {
  FString str1 = "StaticMesh'/Game/Model/";
  FString str2 = "/Mesh/";
  FString str3 = ".";
  FString str4 = "'";
  FString model_name = modelData->name();
  FString file_name = str1 + model_name + str2 + model_name + str3 + model_name + str4;
  //UStaticMesh* loadObj1 = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Game/ArchVis/Mesh/SM_Couch_1seat.SM_Couch_1seat'"), NULL, LOAD_None, NULL);
  UStaticMesh* loadObj = LoadObject<UStaticMesh>(NULL, *file_name, NULL, LOAD_None, NULL);
  
  this->StaticMeshComponent->StaticMesh = loadObj;
  this->StaticMeshComponent->RelativeLocation = modelData->position();
  //float angle = (modelData->rotation_z() / M_PI) * 360;
  //this->StaticMeshComponent->RelativeRotation.Yaw = angle;
  
  
}


