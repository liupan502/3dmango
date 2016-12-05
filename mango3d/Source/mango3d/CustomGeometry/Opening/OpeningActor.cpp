// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"

#include "OpeningActor.h"
#define _USE_MATH_DEFINES
#include <math.h>


// Sets default values
AOpeningActor::AOpeningActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  USphereComponent* sphere = CreateDefaultSubobject<USphereComponent>(TEXT("sphere"));
  RootComponent = sphere;
  opening_mesh_component_ = CreateDefaultSubobject<UOpeningMeshComponent>(TEXT("GeneratedOpeningMesh"));
  //wall_mesh->TestInit();
  //RootComponent = opening_mesh_component_;
  opening_mesh_component_->AttachTo(RootComponent);
  static_mesh_component_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OpeningStaticMesh"));
  static_mesh_component_->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AOpeningActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOpeningActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AOpeningActor::InitWithOpeningData( OpeningData* openingData,   WallData* wallData) {
  opening_mesh_component_->InitWithOpeningData(openingData,wallData);
  
  FString str1 = "StaticMesh'/Game/Model/";
  FString str2 = "/Mesh/";
  FString str3 = ".";
  FString str4 = "'";
  FString model_name = "luodichuang";
  OPENING_TYPE opening_type = openingData->opening_type();
  switch (opening_type) {
  case OPENING_SINGLE_DOOR:
    model_name = "door";
    break;
  default:
    break;
  }
  FString file_name = str1 + model_name + str2 + model_name + str3 + model_name + str4;
  UStaticMesh* loadObj = LoadObject<UStaticMesh>(NULL, *file_name, NULL, LOAD_None, NULL);
  static_mesh_component_->StaticMesh = loadObj;
  static_mesh_component_->RelativeLocation = openingData->position();
  float angle = (openingData->rotation_z() / M_PI) * 180;
  static_mesh_component_->RelativeRotation.Yaw = angle;
}

