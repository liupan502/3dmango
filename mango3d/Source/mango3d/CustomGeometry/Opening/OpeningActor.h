// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "OpeningMeshComponent.h"
#include "Entity/OpeningData.h"
#include "Entity/WallData.h"
#include "OpeningActor.generated.h"

UCLASS()
class MANGO3D_API AOpeningActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpeningActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  virtual void InitWithOpeningData( OpeningData* openingData, WallData* wallData);

protected:

  void AddSpotLights(OpeningData* openingData);
  UPROPERTY(EditAnywhere)
  UOpeningMeshComponent* opening_mesh_component_;
  UStaticMeshComponent* static_mesh_component_;
	
};
