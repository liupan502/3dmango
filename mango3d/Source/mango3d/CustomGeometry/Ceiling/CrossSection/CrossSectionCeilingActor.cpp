// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Util/CustomGeometryUtil.h"
#include "CrossSectionCeilingActor.h"


// Sets default values
ACrossSectionCeilingActor::ACrossSectionCeilingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  cross_section_ceiling_mesh_component_ = CreateDefaultSubobject<UCrossSectionCeilingMeshComponent>(TEXT("GeneratedCeilingMesh"));
  cross_section_ceiling_mesh_component_->SetVisibility(false);
  static_mesh_component_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratedStaticCeilingMesh"));
  static_mesh_component_->SetMobility(EComponentMobility::Static);
  static_mesh_component_->SetVisibility(true);
  RootComponent = static_mesh_component_;

}

// Called when the game starts or when spawned
void ACrossSectionCeilingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrossSectionCeilingActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACrossSectionCeilingActor::InitWithCrossSectionCeilingData(CrossSectionCeilingData* data, RoomData* roomData) {
  cross_section_ceiling_mesh_component_->InitWithCrossSectionCeilingData(data,roomData);
  FString mesh_name = data->name() + "_ceiling";
  UStaticMesh* static_mesh = GetStaticMesh(cross_section_ceiling_mesh_component_, mesh_name);
  static_mesh_component_->StaticMesh = static_mesh;
  static_mesh_component_->bOverrideLightMapRes = 1;
  static_mesh_component_->OverriddenLightMapRes = 512;
}

