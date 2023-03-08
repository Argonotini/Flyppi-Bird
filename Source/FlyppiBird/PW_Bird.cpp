// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_Bird.h"

#include "Blueprint/UserWidget.h"

// Sets default values
APW_Bird::APW_Bird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// setup root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// setup mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	//----------------

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Mesh);
	CameraBoom->TargetArmLength = 600.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void APW_Bird::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetSimulatePhysics(true);
	Mesh->BodyInstance.bLockXTranslation = true;
	Mesh->BodyInstance.bLockYTranslation = true;
	Mesh->BodyInstance.bLockXRotation = true;
	Mesh->BodyInstance.bLockYRotation = true;
	Mesh->BodyInstance.bLockZRotation = true;
	Mesh->BodyInstance.bNotifyRigidBodyCollision = true;
	Mesh->OnComponentHit.AddDynamic(this, &APW_Bird::OnMeshHit);

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}

// Called every frame
void APW_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APW_Bird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APW_Bird::Jump);
}

void APW_Bird::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jumping"));
	Mesh->BodyInstance.SetLinearVelocity(FVector::UpVector*JumpForce, false);
}

void APW_Bird::OnMeshHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult &Hit)
{
	//FString HitActorname = OtherActor->GetFName().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("Hit by %s"), *HitActorname);

	GetWorld()->GetFirstPlayerController()->Pause();

	UUserWidget *WidgRetry = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);
	WidgRetry->AddToViewport();

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

