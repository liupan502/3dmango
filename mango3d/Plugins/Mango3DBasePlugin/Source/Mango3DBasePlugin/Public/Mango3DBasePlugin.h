// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"
#include "TimerManager.h"
//#include "TimerProcessObject.h"


class UTimerProcessObject;
class FMango3DBasePluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
  UTimerProcessObject* timer_process_object_;
  FTimerHandle grab_scene_timer_handle_;
  void OnMapOpenedPorcess(const FString& Filename, bool bLoadAsTemplate);
};