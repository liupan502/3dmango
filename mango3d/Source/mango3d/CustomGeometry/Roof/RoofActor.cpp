// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "RoofActor.h"
#include "Entity/RoomData.h"
#include "RoofMeshComponent.h"
#include "Util/CustomGeometryUtil.h"


// Sets default values
ARoofActor::ARoofActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  //USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
  //RootComponent = SphereComponent;
  roof_mesh_component_ = CreateDefaultSubobject<URoofMeshComponent>(TEXT("GeneratedRoofMesh"));
  roof_mesh_component_->SetVisibility(false);
  //roof_mesh_component_->SetMobility(EComponentMobility::Static);
  //wall_mesh->TestInit();

  static_mesh_component_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratedStaticRoofMesh"));
  static_mesh_component_->SetMobility(EComponentMobility::Static);
  static_mesh_component_->SetVisibility(true);
  RootComponent = static_mesh_component_;

}

// Called when the game starts or when spawned
void ARoofActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoofActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ARoofActor::InitWithRoomData(const RoomData* roomData) {
  roof_mesh_component_->InitWithRoomData(roomData);
  FString mesh_name = roomData->name() + "_roof";
  UStaticMesh* static_mesh = GetStaticMesh(roof_mesh_component_,mesh_name);
  static_mesh_component_->StaticMesh = static_mesh;
}

