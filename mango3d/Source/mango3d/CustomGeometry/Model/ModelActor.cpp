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
  FString model_name = modelData->model_name();
  FString file_name = str1 + model_name + str2 + model_name + str3 + model_name + str4;
  //UStaticMesh* loadObj1 = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Game/ArchVis/Mesh/SM_Couch_1seat.SM_Couch_1seat'"), NULL, LOAD_None, NULL);
  UStaticMesh* loadObj = LoadObject<UStaticMesh>(NULL, *file_name, NULL, LOAD_None, NULL);
  
  int model_type = modelData->model_type();
  if (model_type == 2) {
    UWorld* world = GWorld;
    ASpotLight* spot_light = world->SpawnActor<ASpotLight>(modelData->position()+FVector(0.0,0.0,253.0), FRotator::ZeroRotator);
    //spot_light->SpotLightComponent->LightColor = FLinearColor(0.792, 0.878, 1.0).ToFColor(false);
    spot_light->SpotLightComponent->InnerConeAngle = 36;
    spot_light->SpotLightComponent->OuterConeAngle = 54;
    spot_light->SpotLightComponent->SetMobility(EComponentMobility::Static);
    spot_light->SpotLightComponent->RelativeRotation = FRotator(270, 0, 0);
    spot_light->SpotLightComponent->bUseIESBrightness = 1;
    spot_light->SpotLightComponent->IESTexture = LoadObject<UTextureLightProfile>(NULL, 
      TEXT("TextureLightProfile'/Game/Model/19.19'"), NULL, LOAD_None, NULL);
    int a = 0;
  }

  this->StaticMeshComponent->StaticMesh = loadObj;
  this->StaticMeshComponent->RelativeLocation = modelData->position();
  float angle = (modelData->rotation_z() / M_PI) * 180;
  this->StaticMeshComponent->RelativeRotation.Yaw = angle;
  this->StaticMeshComponent->bOverrideLightMapRes = 1;
  this->StaticMeshComponent->OverriddenLightMapRes = 256;
  
  
}


