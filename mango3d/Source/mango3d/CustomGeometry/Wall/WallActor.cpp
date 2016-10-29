// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "WallActor.h"
#include "WallMeshComponent.h"


// Sets default values
AWallActor::AWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  wall_mesh_component_ = NULL;
  
  /*USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
  RootComponent = SphereComponent;
  UWallMeshComponent* wall_mesh = CreateDefaultSubobject<UWallMeshComponent>(TEXT("GeneratedMesh"));
  wall_mesh->TestInit();
  wall_mesh->AttachTo(RootComponent);*/
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
  if (wall_mesh_component_ == NULL) {
    wall_mesh_component_ = CreateDefaultSubobject<UWallMeshComponent>(TEXT("GeneratedMesh"));
  }

  wall_mesh_component_->InitWithWallData(wallData, openings);
}

