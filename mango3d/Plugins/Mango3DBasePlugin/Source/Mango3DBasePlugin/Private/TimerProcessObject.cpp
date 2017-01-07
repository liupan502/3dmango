// Fill out your copyright notice in the Description page of Project Settings.


#include "Mango3DBasePlugin.h"
#include "TimerProcessObject.h"
#include "LevelEditor.h"
#include "Entity/WallData.h"
#include "Entity/CornerData.h"
#include "Entity/CeilingData.h"
#include "CustomGeometry/Room/RoomActor.h"
#include "CustomGeometry/Roof/RoofActor.h"
#include "CustomGeometry/Floor/FloorActor.h"
#include "CustomGeometry/Opening/OpeningActor.h"
#include "CustomGeometry/OutsideWall/OutsideWallActor.h"
#include "CustomGeometry/Model/ModelActor.h"
#include "CustomGeometry/Ceiling/CrossSection/CrossSectionCeilingActor.h"
#include "Util/CustomGeometryUtil.h"
#include "Util/PolygonUtil.h"


#include "Util/ShareMemoryUtil.h"

#include "Lightmass/LightmassImportanceVolume.h"
#include "Engine/PostProcessVolume.h"
#include "Builders/EditorBrushBuilder.h"
#include "Builders/CubeBuilder.h"

void CreatePostProcessVolume(DesignData* designData) {
  TArray<WallData*> wall_datas = designData->GetOutsideWalls();
  TArray<FVector2D> outside_polygon;
  for (int i = 0; i < wall_datas.Num(); i++) {
    int index = i;
    int next_index = (i + 1) % wall_datas.Num();
    CornerData* corner = wall_datas[index]->GetConnectedCorner(wall_datas[next_index]);
    FVector corner_position = corner->position();
    outside_polygon.Add(FVector2D(corner_position.X, corner_position.Y));
  }

  TArray<FVector2D> rect = GetBoundingRect(outside_polygon);
  float height = FVector2D::Distance(rect[0], rect[1]);
  float width = FVector2D::Distance(rect[0], rect[3]);

  UWorld* world = GWorld;
  APostProcessVolume* post_process_volume =
    world->SpawnActor<APostProcessVolume>(FVector(), FRotator::ZeroRotator);

  UCubeBuilder* cube_builder = NewObject<UCubeBuilder>();
  cube_builder->X = width*1.4;
  cube_builder->Y = height*1.4;
  cube_builder->Z = 280 * 1.4;

  CreateBrushForVolumeActor(post_process_volume, cube_builder);
  FVector2D rect_center(0.0, 0.0);
  for (int i = 0; i < rect.Num(); i++) {
    rect_center = rect_center + rect[i];
  }
  rect_center = rect_center / (rect.Num());
  post_process_volume->BrushComponent->RelativeLocation = FVector(rect_center, 140);

  FPostProcessSettings& setting = post_process_volume->Settings;

  uint32 enabled = 1;
  setting.bOverride_SceneFringeIntensity = enabled;

  setting.bOverride_VignetteIntensity = enabled;
  setting.VignetteIntensity = 0.0;

  setting.bOverride_BloomIntensity = enabled;
  setting.BloomIntensity = 0.5;

  setting.bOverride_BloomThreshold = enabled;
  setting.bOverride_BloomSizeScale = enabled;
  setting.bOverride_Bloom1Size = enabled;
  setting.bOverride_Bloom2Size = enabled;
  setting.bOverride_Bloom3Size = enabled;
  setting.bOverride_Bloom4Size = enabled;
  setting.bOverride_Bloom5Size = enabled;
  setting.bOverride_Bloom6Size = enabled;

  setting.bOverride_BloomDirtMaskIntensity = enabled;

  setting.bOverride_AutoExposureHighPercent = enabled;
  setting.AutoExposureHighPercent = 98.0;
  setting.bOverride_AutoExposureLowPercent = enabled;
  setting.AutoExposureLowPercent = 52.0;
  setting.bOverride_AutoExposureMinBrightness = enabled;
  setting.AutoExposureMinBrightness = 1.0;
  setting.bOverride_AutoExposureMaxBrightness = enabled;
  setting.bOverride_AutoExposureBias = enabled;

  setting.bOverride_LensFlareIntensity = enabled;

  setting.bOverride_AmbientOcclusionIntensity = enabled;
  setting.bOverride_AmbientOcclusionStaticFraction = enabled;
  setting.bOverride_AmbientOcclusionRadius = enabled;
  setting.bOverride_AmbientOcclusionRadiusInWS = enabled;
  //setting.AmbientOcclusionRadiusInWS = enabled;
  setting.bOverride_AmbientOcclusionFadeDistance = enabled;
  setting.bOverride_AmbientOcclusionFadeRadius = enabled;
  setting.bOverride_AmbientOcclusionPower = enabled;
  setting.AmbientOcclusionPower = 3.0;
  setting.bOverride_AmbientOcclusionBias = enabled;
  setting.AmbientOcclusionBias = 3.0;
  setting.bOverride_AmbientOcclusionQuality = enabled;
  setting.AmbientOcclusionQuality = 100.0;
  setting.bOverride_AmbientOcclusionMipBlend = enabled;
  setting.bOverride_AmbientOcclusionMipScale = enabled;
  setting.bOverride_AmbientOcclusionMipThreshold = enabled;

  setting.bOverride_ScreenSpaceReflectionMaxRoughness = enabled;
  setting.ScreenSpaceReflectionMaxRoughness = 1.0;
}

void CreateLightmassImportanceVolume(DesignData* designData) {
  TArray<WallData*> wall_datas = designData->GetOutsideWalls();
  TArray<FVector2D> outside_polygon;
  for (int i = 0; i < wall_datas.Num(); i++) {
    int index = i;
    int next_index = (i + 1) % wall_datas.Num();
    CornerData* corner = wall_datas[index]->GetConnectedCorner(wall_datas[next_index]);
    FVector corner_position = corner->position();
    outside_polygon.Add(FVector2D(corner_position.X, corner_position.Y));
  }

  TArray<FVector2D> rect = GetBoundingRect(outside_polygon);
  float height = FVector2D::Distance(rect[0], rect[1]);
  float width = FVector2D::Distance(rect[0], rect[3]);
  
  UWorld* world = GWorld;
  ALightmassImportanceVolume* importance_volume = 
    world->SpawnActor<ALightmassImportanceVolume>(FVector(), FRotator::ZeroRotator);
  
  UCubeBuilder* cube_builder = NewObject<UCubeBuilder>();
  cube_builder->X = width*1.2;
  cube_builder->Y = height*1.2;
  cube_builder->Z = 280 * 1.2;
  
  CreateBrushForVolumeActor(importance_volume, cube_builder);
  FVector2D rect_center(0.0,0.0);
  for (int i = 0; i < rect.Num(); i++) {
    rect_center = rect_center + rect[i];
  }
  rect_center = rect_center / (rect.Num());
  importance_volume->BrushComponent->RelativeLocation = FVector(rect_center, 140);
}

void CreateBoxReflectionCapture(DesignData* designData) {
  TArray<WallData*> wall_datas = designData->GetOutsideWalls();
  TArray<FVector2D> outside_polygon;
  for (int i = 0; i < wall_datas.Num(); i++) {
    int index = i;
    int next_index = (i + 1) % wall_datas.Num();
    CornerData* corner = wall_datas[index]->GetConnectedCorner(wall_datas[next_index]);
    FVector corner_position = corner->position();
    outside_polygon.Add(FVector2D(corner_position.X, corner_position.Y));
  }

  TArray<FVector2D> rect = GetBoundingRect(outside_polygon);
  float height = FVector2D::Distance(rect[0], rect[1]);
  float width = FVector2D::Distance(rect[0], rect[3]);

  UWorld* world = GWorld;  
  ABoxReflectionCapture* box_reflection_capture =
    world->SpawnActor<ABoxReflectionCapture>(FVector(), FRotator::ZeroRotator);
  //box_reflection_capture->CaptureComponent
  box_reflection_capture->CaptureComponent->RelativeScale3D = FVector(width*1.2,height*1.2,280*1.2);
  FVector2D rect_center(0.0, 0.0);
  for (int i = 0; i < rect.Num(); i++) {
    rect_center = rect_center + rect[i];
  }
  rect_center = rect_center / (rect.Num());
  box_reflection_capture->CaptureComponent->RelativeLocation = FVector(rect_center, 140);
}

void UTimerProcessObject::GrabSceneData() {
  update_design_data();
  //UCubeBuilder* cube_builder = NewObject<UCubeBuilder>();
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
  FVector location(0.0, 0.0, 0.0);
  TArray<WallData*> walls = design_data_.GetWalls();
  for (int i = 0; i < walls.Num(); i++) {
    TArray<OpeningData*> openings = design_data_.GetRelatedOpenings(walls[i]);
    for (int j = 0; j < openings.Num(); j++) {
      AOpeningActor* opening_actor = world->SpawnActor<AOpeningActor>(location, FRotator::ZeroRotator);
      opening_actor->InitWithOpeningData(openings[j],walls[i]);
    }
  } 

  TArray<RoomData*> rooms = design_data_.GetRooms();
  for (int i = 0; i < rooms.Num(); i++) {
    RoomData* room = rooms[i];    
    ARoofActor* roof_actor = world->SpawnActor<ARoofActor>(location, FRotator::ZeroRotator);
    roof_actor->InitWithRoomData(room);
    AFloorActor* floor_actor = world->SpawnActor<AFloorActor>(location, FRotator::ZeroRotator);
    floor_actor->InitWithRoomData(room);

    std::vector<WallData*> walls = room->GetWalls();
    for (int j = 0; j< walls.size(); j++) {
      WallData* wall = walls[j];
      TArray<OpeningData*> openings = design_data_.GetRelatedOpenings(wall);
      
      AWallActor* wall_actor = world->SpawnActor<AWallActor>(location, FRotator::ZeroRotator);
      wall_actor->InitWithWallData(wall, openings, room);
    }
  }

  AOutsideWallActor* outside_wall_actor = world->SpawnActor<AOutsideWallActor>(location, FRotator::ZeroRotator);
  outside_wall_actor->InitWithDesignData(&design_data_);

  TArray<ModelData*> model_datas = design_data_.GetModels();
  for (int i = 0; i < model_datas.Num(); i++) {
    AModelActor* model_actor = world->SpawnActor<AModelActor>(location, FRotator::ZeroRotator);
    model_actor->InitWithModelData(model_datas[i]);
  }
  TArray<CrossSectionCeilingData*> ceiling_datas = design_data_.GetCrossSectionCeilingData();
  for (int i = 0; i < ceiling_datas.Num(); i++) {
    ACrossSectionCeilingActor* ceiling_actor = world->SpawnActor<ACrossSectionCeilingActor>(
      location, FRotator::ZeroRotator);
    RoomData* related_room_data = NULL;
    for (int j = 0; j < rooms.Num(); j++) {
      if (rooms[i]->name() == ceiling_datas[i]->room_name()) {
        related_room_data = rooms[i];
        break;
      }
    }
    ceiling_actor->InitWithCrossSectionCeilingData(ceiling_datas[i], related_room_data);
  }
  CreateLightmassImportanceVolume(&design_data_);
  CreatePostProcessVolume(&design_data_);
  CreateBoxReflectionCapture(&design_data_);
}


