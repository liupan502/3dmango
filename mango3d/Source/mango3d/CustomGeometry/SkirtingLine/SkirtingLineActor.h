// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SkirtingLineActor.generated.h"

class WallData;
class OpeningData;
class RoomData;
class USkirtingLineMeshComponent;
//class USkirtingLineMeshComponent;
UCLASS()
class MANGO3D_API ASkirtingLineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkirtingLineActor();

  void InitWithWallData(WallData* wallData, TArray<OpeningData*>& openings,RoomData* roomData);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

  USkirtingLineMeshComponent* skirting_line_mesh_component_;
	
  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* static_mesh_component_;
	
};
