// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "mango3dGameMode.generated.h"


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
	
  int design_id_;

  //DesignData design_data_;
	
};
