// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Util/ShareMemoryUtil.h"
#include "CustomGeometry/Wall/WallActor.h"
#include "mango3dGameMode.h"


void Amango3dGameMode::BeginPlay() {
  
  UWorld* world = GetWorld();  
  design_id_ = 0;
  world->GetTimerManager().SetTimer(update_design_data_timer_handle_, this,
    &Amango3dGameMode::update_design_data, 1.0f,true);
}

void Amango3dGameMode::update_design_data() {
  FString design_data;
  int design_id = design_id_;
  if (GetNewDesignData(design_data, design_id)) {
    design_id_ = design_id;
    TSharedRef<TJsonReader<TCHAR>> reader_ref =  FJsonStringReader::Create(design_data);
    TSharedPtr<FJsonObject> json_object_ptr;
    if (FJsonSerializer::Deserialize(reader_ref, json_object_ptr)) {
      FJsonObject* json_object = json_object_ptr.Get();
      design_data_.InitWithJsonObject(*json_object);
      update_world_geometry();
    }
    
  }
}

void Amango3dGameMode::update_world_geometry() {
  UWorld* world = GetWorld();
  TArray<WallData*> walls = design_data_.GetWalls();
  for (int i = 0; i < walls.Num(); i++) {
    WallData* wall = walls[i];    
    TArray<OpeningData*> openings = design_data_.GetRelatedOpenings(wall);   
    FVector location(0.0, 0.0, 0.0);
    AWallActor* wall_actor = world->SpawnActor<AWallActor>( location, FRotator::ZeroRotator);
    wall_actor->InitWithWallData(wall, openings);
  } 
}




