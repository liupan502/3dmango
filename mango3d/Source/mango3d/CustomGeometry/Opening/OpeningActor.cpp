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
    AddSpotLights(openingData);
    break;
  }
  FString file_name = str1 + model_name + str2 + model_name + str3 + model_name + str4;
  UStaticMesh* loadObj = LoadObject<UStaticMesh>(NULL, *file_name, NULL, LOAD_None, NULL);
  static_mesh_component_->StaticMesh = loadObj;
  static_mesh_component_->RelativeLocation = openingData->position();
  float angle = (openingData->rotation_z() / M_PI) * 180;
  static_mesh_component_->RelativeRotation.Yaw = angle;
}

void AOpeningActor::AddSpotLights(OpeningData* openingData) {
  UWorld* world = GWorld;
  float length = openingData->length();
  float height = openingData->height();
  TArray<ASpotLight*> spot_lights;
  ASpotLight* spot_light1 = world->SpawnActor<ASpotLight>(openingData->position()+FVector(0,0.3*length,0.6*height), FRotator::ZeroRotator);
  spot_lights.Add(spot_light1);
  ASpotLight* spot_light2 = world->SpawnActor<ASpotLight>(openingData->position()+FVector(0,0.3*length,  0.4*height) , FRotator::ZeroRotator);
  spot_lights.Add(spot_light2);
  ASpotLight* spot_light3 = world->SpawnActor<ASpotLight>(openingData->position() + FVector(0,-0.3*length,  0.6*height), FRotator::ZeroRotator);
  spot_lights.Add(spot_light3);
  ASpotLight* spot_light4 = world->SpawnActor<ASpotLight>(openingData->position() + FVector(0,-0.3*length,  0.4*height), FRotator::ZeroRotator);
  spot_lights.Add(spot_light4);

  for (int i = 0; i < spot_lights.Num(); i++) {    
    spot_lights[i]->SpotLightComponent->LightColor = FLinearColor(0.792, 0.878, 1.0).ToFColor(false);    
    spot_lights[i]->SpotLightComponent->OuterConeAngle = 80;
    spot_lights[i]->SpotLightComponent->InnerConeAngle = 70.0;
    spot_lights[i]->SpotLightComponent->AttenuationRadius = 5000.0;
    spot_lights[i]->SpotLightComponent->SourceRadius = 50;
    spot_lights[i]->SpotLightComponent->SetMobility(EComponentMobility::Static);
    spot_lights[i]->SpotLightComponent->RelativeRotation = FRotator(0, 0, 0);
    
  }
}