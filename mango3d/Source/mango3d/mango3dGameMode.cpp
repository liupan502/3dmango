// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Util/ShareMemoryUtil.h"
#include "mango3dGameMode.h"


void Amango3dGameMode::BeginPlay() {
  
  UWorld* world = GetWorld();  
  design_id_ = 0;
  world->GetTimerManager().SetTimer(update_design_data_timer_handle_, this,
    &Amango3dGameMode::update_design_data, 1.0f,true);
}

void Amango3dGameMode::update_design_data() {
  FString design_data;
  int design_id;
  if (GetNewDesignData(design_data, design_id)) {

    design_id_ = design_id;

    //design_data_.InitWithJsonObject()
  }
}




