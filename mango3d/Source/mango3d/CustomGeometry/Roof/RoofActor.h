// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoofActor.generated.h"


class RoomData;
class URoofMeshComponent;
UCLASS()
class MANGO3D_API ARoofActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoofActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  void InitWithRoomData(const RoomData* roomData);

private:

  
  URoofMeshComponent* roof_mesh_component_;

  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* static_mesh_component_;
	
};
