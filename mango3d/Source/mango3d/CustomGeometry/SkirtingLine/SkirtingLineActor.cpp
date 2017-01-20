// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "SkirtingLineActor.h"
#include "Entity/WallData.h"
#include "SkirtingLineMeshComponent.h"

// Sets default values
ASkirtingLineActor::ASkirtingLineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  skirting_line_mesh_component_ = CreateDefaultSubobject<USkirtingLineMeshComponent>(TEXT("GeneratedMesh"));
  skirting_line_mesh_component_->SetMobility(EComponentMobility::Static);
  skirting_line_mesh_component_->SetVisibility(false);
  static_mesh_component_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratedStaticMesh"));
  static_mesh_component_->SetMobility(EComponentMobility::Static);
  static_mesh_component_->SetVisibility(true);
  RootComponent = static_mesh_component_;
}

// Called when the game starts or when spawned
void ASkirtingLineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkirtingLineActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASkirtingLineActor::InitWithWallData(WallData* wallData, TArray<OpeningData*>& openings, RoomData* roomData) {
  skirting_line_mesh_component_->InitWithWallData(wallData, openings, roomData);
  FString mesh_name = wallData->name()+"sk";
  UStaticMesh* static_mesh = GetStaticMesh(skirting_line_mesh_component_, mesh_name);
  static_mesh_component_->StaticMesh = static_mesh;
  static_mesh_component_->bOverrideLightMapRes = 1;
  static_mesh_component_->OverriddenLightMapRes = 512;
}

