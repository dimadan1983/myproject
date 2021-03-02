// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeomeryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)
// Sets default values
ABaseGeomeryActor::ABaseGeomeryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);

}

// Called when the game starts or when spawned
void ABaseGeomeryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	printTransform();
	//printStringTypes();
	//printTypes();
	
}

// Called every frame
void ABaseGeomeryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//z = z0 + amplitude * sin(freq * t);
	float time = GetWorld()->GetTimeSeconds();
	FVector CurrentLocation = GetActorLocation();

	CurrentLocation.Z = InitialLocation.Z + amplitude * FMath::Sin(Frequency * time);
	SetActorLocation(CurrentLocation);

}

void ABaseGeomeryActor::printTypes()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);
	UE_LOG(LogTemp, Warning, TEXT("Health: %.2f"), Health);
	UE_LOG(LogTemp, Warning, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogTemp, Warning, TEXT("Has Weapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeomeryActor::printStringTypes()
{
	FString Name = "John Connor";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

	FString WeaponNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString HasWeaponStr = "Has Weapon = " + FString(HasWeapon ? "true" : "false");

	FString Stat = FString::Printf(TEXT("\n=== All stat === \n%s \n%s \n%s ==="), *WeaponNumStr, *HealthStr, *HasWeaponStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
}

void ABaseGeomeryActor::printTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogTemp, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Rotaion %s"), *Rotation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Scale %s"), *Scale.ToString());

	UE_LOG(LogTemp, Warning, TEXT("Human Transform %s"), *Transform.ToHumanReadableString());
}

