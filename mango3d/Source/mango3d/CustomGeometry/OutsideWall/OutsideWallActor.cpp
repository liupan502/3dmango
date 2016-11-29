// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "OutsideWallActor.h"


// Sets default values
AOutsideWallActor::AOutsideWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  outside_wall_mesh_component_ = CreateDefaultSubobject<UOutsideWallMeshComponent>(TEXT("GeneratedOutsideWallMesh"));

  RootComponent = outside_wall_mesh_component_;

}

// Called when the game starts or when spawned
void AOutsideWallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOutsideWallActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AOutsideWallActor::InitWithDesignData(DesignData* designData){
  outside_wall_mesh_component_->InitWithDesignData(designData);
}

