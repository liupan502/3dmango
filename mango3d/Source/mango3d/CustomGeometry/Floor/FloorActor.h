// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FloorMeshComponent.h"
#include "FloorActor.generated.h"

class RoomData;
UCLASS()
class MANGO3D_API AFloorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  void InitWithRoomData(const RoomData* roomData);


private:
  UFloorMeshComponent* floor_mesh_component_;
	
};
