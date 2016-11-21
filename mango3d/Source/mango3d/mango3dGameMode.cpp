// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Util/ShareMemoryUtil.h"
#include "CustomGeometry/Wall/WallActor.h"
#include "CustomGeometry/Floor/FloorActor.h"
#include "CustomGeometry/Roof/RoofActor.h"

#include "mango3dGameMode.h"


void Amango3dGameMode::BeginPlay() {
  
  /*UWorld* world = GetWorld();  
  design_id_ = 0;
  b_test_ = true;
  b_build_mass_ = false;
  world->GetTimerManager().SetTimer(update_design_data_timer_handle_, this,
    &Amango3dGameMode::update_design_data, 1.0f,true);
  */
  //UObjectLibrary* object_library = UObjectLibrary::CreateLibrary(UStaticMesh::StaticClass(), false, true);
  //int result = object_library->LoadAssetDataFromPath(TEXT("/content/staticmesh"));
  //FStringAssetReference asset = "UStaticMesh'/content/staticmesh/M_CoathookBack.M_CoathookBack'";
  //UObject* itemObj = asset.ResolveObject();
  //FStringAssetReference ar = 
  /*if (GIsEditor == true) {
    int a = 0;
  }
  else
  {
    int a = 0;
  }*/
  /*UStaticMesh* loadObj = LoadObject<UStaticMesh>( NULL, TEXT("StaticMesh'/Game/ArchVis/Mesh/SM_Couch_1seat.SM_Couch_1seat'"), NULL, LOAD_None, NULL);
  
  
  int umi_num   = loadObj->Materials.Num();
  for (int i = 0; i < umi_num; i++) {
    UMaterialInterface* umi = loadObj->GetMaterial(i);
    int a = 0;
  }

  FVector location(0.0, 0.0, 0.0);
  AStaticMeshActor* static_mesh_actor = world->SpawnActor<AStaticMeshActor>(location, FRotator::ZeroRotator);
  static_mesh_actor->StaticMeshComponent->StaticMesh = loadObj;
  */  
  /*if (loadObj != nullptr)
  {
    UBlueprint* ubp = Cast<UBlueprint>(loadObj);
    AActor* spawnActor = GetWorld()->SpawnActor<AActor>(ubp->GeneratedClass);
    UE_LOG(LogClass, Log, TEXT("Success"));
  }*/

  //IAssetRegistry ar = FAssetRegistryModule::Get();
  //FStringAssetReference ref(TEXT("/Game/staticmesh1/zuhegui_Box007.uasset"));
  //FStringAssetReference ref(TEXT("C:/Users/liupan/Documents/code/3dmango/mango3d/Content/staticmesh1/zuhegui_Box007.uasset"));
  //FStreamableManager man;
  //UObject* obj = man.SynchronousLoad(ref);

  //int a = 0;
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

  if (b_test_) {
    b_test_ = false;
    UWorld* world = GetWorld();
    UStaticMesh* loadObj = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Game/ArchVis/Mesh/SM_Couch_1seat.SM_Couch_1seat'"), NULL, LOAD_None, NULL);


    int umi_num = loadObj->Materials.Num();
    for (int i = 0; i < umi_num; i++) {
      UMaterialInterface* umi = loadObj->GetMaterial(i);
      int a = 0;
    }


    FVector location(0.0, 0.0, 0.0);
    AStaticMeshActor* static_mesh_actor = world->SpawnActor<AStaticMeshActor>(location, FRotator::ZeroRotator);
    static_mesh_actor->StaticMeshComponent->StaticMesh = loadObj;
    static_mesh_actor->StaticMeshComponent->SetMobility(EComponentMobility::Stationary);
    static_mesh_actor->StaticMeshComponent->SetMobility(EComponentMobility::Static);

    b_build_mass_ = true;
  }
  else if(b_build_mass_){
    //FLevelEditorActionCallbacks::Build_Execute();
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




