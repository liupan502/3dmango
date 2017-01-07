// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CrossSectionCeilingMeshComponent.h"
#include "Entity/CeilingData.h"
#include "Entity/RoomData.h"
#include "CrossSectionCeilingActor.generated.h"

UCLASS()
class MANGO3D_API ACrossSectionCeilingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrossSectionCeilingActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  void InitWithCrossSectionCeilingData(CrossSectionCeilingData* data,RoomData* roomData);

protected:
  UPROPERTY(EditAnywhere)
  UCrossSectionCeilingMeshComponent* cross_section_ceiling_mesh_component_;
  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* static_mesh_component_;
	
};
