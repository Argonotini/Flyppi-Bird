// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_Builds.h"

void APW_Builds::SpawnPillars()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Pillars!"));

	for (size_t i = 0; i < Pillars.Num(); i++)
	{
		if (Pillars[i])
		{
			Pillars[i]->DestroyComponent();
		}
	}
	Pillars.Empty();
	
	for (size_t i = 0; i < NumOfPillars; i++)
	{
		UStaticMeshComponent *smc = (UStaticMeshComponent*)AddComponentByClass(UStaticMeshComponent::StaticClass(), false, FTransform(), true);
		if (smc)
		{
			smc->RegisterComponent();
			smc->SetMobility(EComponentMobility::Movable);
			smc->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			smc->SetWorldLocation(this->GetActorLocation()+FVector(0.f, PillarGap*i, 0.f));
			smc->SetStaticMesh(PillarsMesh);
			Pillars.Add(smc);
		}
	}
	RandomizePillars();
}

void APW_Builds::RandomizePillars()
{
	for (size_t i = 0; i < NumOfPillars; i++)
	{
		Pillars[i]->SetWorldScale3D(FVector(1, 1, FMath::RandRange(1, 2)));
	}
}

// Sets default values
APW_Builds::APW_Builds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void APW_Builds::BeginPlay()
{
	Super::BeginPlay();

	
}

void APW_Builds::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SpawnPillars();
}

// Called every frame
void APW_Builds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Moving pillars
	SetActorLocation(GetActorLocation()+FVector(0, MoveSpeed * DeltaTime, 0));

	if (GetActorLocation().Y < -1*(PillarGap * NumOfPillars + 300))
	{
		SetActorLocation(GetActorLocation() + FVector(0, PillarGap + NumOfPillars + ScreenWidth, 0));
		RandomizePillars();
	}
}

