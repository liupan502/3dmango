// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "FloorActor.h"
#include "Entity/RoomData.h"


// Sets default values
AFloorActor::AFloorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
  RootComponent = SphereComponent;
  floor_mesh_component_ = CreateDefaultSubobject<UFloorMeshComponent>(TEXT("GeneratedRoofMesh"));
  //wall_mesh->TestInit();
  floor_mesh_component_->AttachTo(RootComponent);

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
}

