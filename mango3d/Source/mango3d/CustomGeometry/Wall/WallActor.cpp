// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "WallActor.h"
#include "WallMeshComponent.h"
#include "CustomGeometry/SkirtingLine/SkirtingLineActor.h"
#include "Util/CustomGeometryUtil.h"


// Sets default values
AWallActor::AWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  
  wall_mesh_component_ = CreateDefaultSubobject<UWallMeshComponent>(TEXT("GeneratedMesh"));
  wall_mesh_component_->SetMobility(EComponentMobility::Static);
  wall_mesh_component_->SetVisibility(false);
  static_mesh_component_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratedStaticMesh"));
  static_mesh_component_->SetMobility(EComponentMobility::Static);
  static_mesh_component_->SetVisibility(true);
  RootComponent = static_mesh_component_;
  //wall_mesh->TestInit();
  //wall_mesh_component_->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AWallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWallActor::InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings) {
  

  wall_mesh_component_->InitWithWallData(wallData, openings);
}

void AWallActor::InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings,const RoomData* roomData) {


  wall_mesh_component_->InitWithWallData(wallData, openings, roomData);
  FString mesh_name = wallData->name();
  UStaticMesh* static_mesh = GetStaticMesh(wall_mesh_component_, mesh_name);
  static_mesh_component_->StaticMesh = static_mesh;

  UWorld* world = GWorld;
  FVector location(0.0, 0.0, 0.0);
  ASkirtingLineActor* skirting_line = world->SpawnActor<ASkirtingLineActor>(location, FRotator::ZeroRotator);
  //WallData tmp_wall_data = *wallData;
  //RoomData tmp_room_data = *roomData;
  skirting_line->InitWithWallData((WallData*)wallData, openings, (RoomData*)roomData);

  static_mesh_component_->bOverrideLightMapRes = 1;
  static_mesh_component_->OverriddenLightMapRes = 512;
  
}

