// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "RoomActor.h"


// Sets default values
ARoomActor::ARoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
  RootComponent = SphereComponent;

  floor_component_ = CreateDefaultSubobject<UFloorMeshComponent>(TEXT("floorMesh"));
  floor_component_->AttachTo(RootComponent);

  roof_component_ = CreateDefaultSubobject<URoofMeshComponent>(TEXT("roofMesh"));
  roof_component_->AttachTo(RootComponent);


}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ARoomActor::InitWithRoomData(const RoomData* roomData,  std::map<FString, OpeningData*> openingMap) {
  floor_component_->InitWithRoomData(roomData);

  roof_component_->InitWithRoomData(roomData);

  std::vector<WallData*> wall_datas = roomData->GetWalls();

  wall_components_.Empty();

  for (int i = 0; i < wall_datas.size(); i++) {

    WallData* wall_data = wall_datas[i];

    TArray<OpeningData*> openings;
    std::set<FString> opening_names = wall_data->opening_names();
    for (std::set<FString>::iterator it = opening_names.begin();
      it != opening_names.end(); it++) {      
      openings.Add(openingMap[(*it)]);
    }
    //UWallMeshComponent* wall_component = NULL;
    //NewNamedObject<UWallMeshComponent> (wall_component,"walMesh");//CreateDefaultSubobject<UWallMeshComponent>(TEXT("walMesh"));
    UWallMeshComponent* wall_component = ConstructObject<UWallMeshComponent>(UWallMeshComponent::StaticClass(), (UObject*)GetTransientPackage(),TEXT("my_wall"));
    
    wall_component->InitWithWallData(wall_data, openings,roomData);
    bool status = wall_component->AttachTo(RootComponent);
    wall_components_.Add(wall_component);
  }


}

