// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "FloorActor.h"
#include "Entity/RoomData.h"
#include "Util/CustomGeometryUtil.h"


// Sets default values
AFloorActor::AFloorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  
  floor_mesh_component_ = CreateDefaultSubobject<UFloorMeshComponent>(TEXT("GeneratedRoofMesh"));
  floor_mesh_component_->SetVisibility(false);
  static_mesh_component_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratedStaticRoofMesh"));
  static_mesh_component_->SetMobility(EComponentMobility::Static);
  static_mesh_component_->SetVisibility(true);
  RootComponent = static_mesh_component_;

}

// Called when the game starts or when spawned
void AFloorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFloorActor::InitWithRoomData(const RoomData* roomData) {
  floor_mesh_component_->InitWithRoomData(roomData);
  FString mesh_name = roomData->name() + "_floor";
  UStaticMesh* static_mesh = GetStaticMesh(floor_mesh_component_, mesh_name);
  static_mesh_component_->StaticMesh = static_mesh;
  static_mesh_component_->bOverrideLightMapRes = 1;
  static_mesh_component_->OverriddenLightMapRes = 512;
}

