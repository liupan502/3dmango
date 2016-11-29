// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Entity/WallData.h"
#include "Entity/OpeningData.h"
#include "Entity/RoomData.h"
#include "WallActor.generated.h"

class UWallMeshComponent;

UCLASS()
class MANGO3D_API AWallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallActor();

  void InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings);

  void InitWithWallData(const WallData* wallData, TArray<OpeningData*>& openings,const RoomData* roomData);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


protected:

  UPROPERTY(EditAnywhere)
  UWallMeshComponent* wall_mesh_component_;

   

	
	
};
