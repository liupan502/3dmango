// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "OutsideWallMeshComponent.h"
#include "Entity/DesignData.h"
#include "OutsideWallActor.generated.h"

UCLASS()
class MANGO3D_API AOutsideWallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOutsideWallActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  void InitWithDesignData(DesignData* designData);

protected:

  UPROPERTY(EditAnywhere)
  UOutsideWallMeshComponent* outside_wall_mesh_component_;
	
};
