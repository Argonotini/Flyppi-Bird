// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PW_Builds.generated.h"

UCLASS()
class FLYPPIBIRD_API APW_Builds : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TArray<UStaticMeshComponent*> Pillars;

	UPROPERTY(EditAnywhere)
	int NumOfPillars = 10;

	UPROPERTY(EditAnywhere)
	float PillarGap = 100.0f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 10.f;

	UPROPERTY(EditAnywhere)
	float ScreenWidth = 1000.f;

	UPROPERTY(EditAnywhere)
	UStaticMesh *PillarsMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent *Root;

	UFUNCTION(BlueprintCallable)
	void SpawnPillars();

	UFUNCTION(BlueprintCallable)
	void RandomizePillars();

	
	
public:	
	// Sets default values for this actor's properties
	APW_Builds();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual  void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
