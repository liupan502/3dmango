// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Object.h"
#include "Entity/DesignData.h"
#include "CustomGeometry/Wall/WallActor.h"
#include "TimerProcessObject.generated.h"

/**
 * 
 */
UCLASS()
class UTimerProcessObject : public UObject
{
	GENERATED_BODY()
public:
  void GrabSceneData();
	
  void update_design_data();

  void update_world_geometry();

  int design_id_;

  DesignData design_data_;

  TArray<AWallActor*> walls_;

  
	
};
