// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Entity/ModelData.h"
#include "ModelActor.generated.h"

/**
 * 
 */
UCLASS()
class MANGO3D_API AModelActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
  AModelActor();
  void InitWithModelData(ModelData* modelData);
protected:

  void init_static_mesh(ModelData* modelData);
  ModelData* model_data_;
	
};
