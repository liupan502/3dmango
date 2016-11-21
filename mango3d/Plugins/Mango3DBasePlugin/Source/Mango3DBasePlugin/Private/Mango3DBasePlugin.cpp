// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#include "Mango3DBasePlugin.h"
#include "Mango3DBasePluginPrivatePCH.h"
#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "FMango3DBasePluginModule"

void FMango3DBasePluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
  FEditorDelegates::OnMapOpened.AddRaw(this, &FMango3DBasePluginModule::OnMapOpenedPorcess);
}

void FMango3DBasePluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FMango3DBasePluginModule::OnMapOpenedPorcess(const FString& Filename, bool bLoadAsTemplate) {
  UWorld* world = GWorld;
  timer_process_object_ = NewObject<UTimerProcessObject>();
  world->GetTimerManager().SetTimer(grab_scene_timer_handle_, timer_process_object_, &UTimerProcessObject::GrabSceneData, 2.0f, true);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMango3DBasePluginModule, Mango3DBasePlugin)