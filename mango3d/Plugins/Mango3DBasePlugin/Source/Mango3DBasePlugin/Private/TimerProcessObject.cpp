// Fill out your copyright notice in the Description page of Project Settings.

#include "Mango3DBasePlugin.h"
#include "TimerProcessObject.h"
#include "LevelEditor.h"
#include "Entity/WallData.h"
#include "CustomGeometry/Roof/RoofActor.h"
#include "CustomGeometry/Model/ModelActor.h"
#include "CustomGeometry/Floor/FloorActor.h"

#include "Util/ShareMemoryUtil.h"

void UTimerProcessObject::GrabSceneData() {
  update_design_data();
}

void UTimerProcessObject::update_design_data() {
  FString design_data;
  int design_id = design_id_;
  if (GetNewDesignData(design_data, design_id)) {
    design_id_ = design_id;
    TSharedRef<TJsonReader<TCHAR>> reader_ref = FJsonStringReader::Create(design_data);
    TSharedPtr<FJsonObject> json_object_ptr;
    if (FJsonSerializer::Deserialize(reader_ref, json_object_ptr)) {
      FJsonObject* json_object = json_object_ptr.Get();
      design_data_.InitWithJsonObject(*json_object);
      update_world_geometry();
    }

  }
}

void UTimerProcessObject::update_world_geometry() {
  UWorld* world = GWorld;
  TArray<WallData*> walls = design_data_.GetWalls();
  for (int i = 0; i < walls.Num(); i++) {
    WallData* wall = walls[i];
    TArray<OpeningData*> openings = design_data_.GetRelatedOpenings(wall);
    FVector location(0.0, 0.0, 0.0);
    AWallActor* wall_actor = world->SpawnActor<AWallActor>(location, FRotator::ZeroRotator);
    wall_actor->InitWithWallData(wall, openings);
  }

  TArray<RoomData*> rooms = design_data_.GetRooms();
  for (int i = 0; i < rooms.Num(); i++) {
    RoomData* room = rooms[i];
    FVector location(0.0, 0.0, 0.0);
    ARoofActor* roof_actor = world->SpawnActor<ARoofActor>(location, FRotator::ZeroRotator);
    roof_actor->InitWithRoomData(room);
    AFloorActor* floor_actor = world->SpawnActor<AFloorActor>(location, FRotator::ZeroRotator);
    floor_actor->InitWithRoomData(room);
  }
}

