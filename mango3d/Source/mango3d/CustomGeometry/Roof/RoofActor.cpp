// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "RoofActor.h"
#include "RoofMeshComponent.h"


// Sets default values
ARoofActor::ARoofActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
  RootComponent = SphereComponent;
  roof_mesh_component_ = CreateDefaultSubobject<URoofMeshComponent>(TEXT("GeneratedRoofMesh"));
  //wall_mesh->TestInit();
  roof_mesh_component_->AttachTo(RootComponent);

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
}

