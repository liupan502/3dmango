// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Entity/DesignData.h"
//#include "AssetRegistryModule.h"
//#include "LevelEditorActions.h"
#include "mango3dGameMode.generated.h"


class AWallActor;

/**
 * 
 */
UCLASS()

class MANGO3D_API Amango3dGameMode : public AGameMode
{
  GENERATED_BODY()
public:
  virtual void BeginPlay();
  
protected:
  FTimerHandle update_design_data_timer_handle_;

  void update_design_data();

  void update_world_geometry();
	
  int design_id_;

  DesignData design_data_;

  TArray<AWallActor*> walls_;

  bool b_test_;

  bool b_build_mass_;
	
};
