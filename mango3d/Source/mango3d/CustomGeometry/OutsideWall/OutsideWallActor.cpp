// Fill out your copyright notice in the Description page of Project Settings.

#include "mango3d.h"
#include "Util/CustomGeometryUtil.h"
#include "Util/PolygonUtil.h"
#include "Entity/WallData.h"
#include "Entity/CornerData.h"
#include "OutsideWallActor.h"

#include "Lightmass/LightmassImportanceVolume.h"
#include "Builders/EditorBrushBuilder.h"
#include "Builders/CubeBuilder.h"
//#include "ActorFactories/ActorFactoryBoxVolume.h"


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
  /*TArray<WallData*> wall_datas = designData->GetOutsideWalls();
  TArray<FVector2D> outside_polygon;
  for (int i = 0; i < wall_datas.Num(); i++) {
    int index = i;
    int next_index = (i + 1) % wall_datas.Num();
    CornerData* corner = wall_datas[index]->GetConnectedCorner(wall_datas[next_index]);
    FVector corner_position = corner->position();
    outside_polygon.Add(FVector2D(corner_position.X, corner_position.Y));
  }
  TArray<FVector2D> rect = GetBoundingRect(outside_polygon);
  float height = FVector2D::Distance(rect[0], rect[1]);
  float width = FVector2D::Distance(rect[0], rect[3]);
  UWorld* world = GWorld;
  ALightmassImportanceVolume* importance_volume = world->SpawnActor<ALightmassImportanceVolume>(FVector(), FRotator::ZeroRotator);
  //UCubeBuilder* cube_builder = (UCubeBuilder*)(importance_volume->BrushBuilder);
  //UCubeBuilder* cube_builder = new UCubeBuilder();//NewObject<UCubeBuilder>();
  //UActorFactoryBoxVolume* fac_vol = NewObject<UActorFactoryBoxVolume>();
  //fac_vol->PostSpawnActor(NULL, NULL);
  /*UCubeBuilder* cube_builder = NewObject<UCubeBuilder>((UObject*)GetTransientPackage(), "light importance", RF_Public | RF_Standalone);
  cube_builder->X = width*1.2;
  cube_builder->Y = height*1.2;
  cube_builder->Z = 280 * 1.2;*/
  //CreateBrushForVolumeActor(importance_volume, cube_builder);
 // cube_builder->X = width*1.2;
 // cube_builder->Y = height*1.2;
 // cube_builder->Z = 280 * 1.2;


}

