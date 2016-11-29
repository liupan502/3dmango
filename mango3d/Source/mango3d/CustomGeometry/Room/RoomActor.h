// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CustomGeometry/Floor/FloorMeshComponent.h"
#include "CustomGeometry/Roof/RoofMeshComponent.h"
#include "CustomGeometry/Wall/WallMeshComponent.h"

#include "Entity/RoomData.h"
#include "Entity/OpeningData.h"
#include "RoomActor.generated.h"

UCLASS()
class MANGO3D_API ARoomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  void InitWithRoomData(const RoomData* roomData, std::map<FString, OpeningData*> openingMap);

  

protected:

  UPROPERTY(EditAnywhere)
  TArray<UWallMeshComponent*> wall_components_;

  UPROPERTY(EditAnywhere)
  URoofMeshComponent* roof_component_;

  UFloorMeshComponent* floor_component_;
	
	
};
