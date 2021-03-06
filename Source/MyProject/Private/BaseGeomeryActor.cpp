// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeomeryActor.h" 
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

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
	// printTransform();
	// printStringTypes();
	// printTypes();

	SetColor(GeometryData.Color);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeomeryActor::OnTimerFired, GeometryData.TimerRate, true);
}

void ABaseGeomeryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Error, TEXT("Actor is destroyed"));

}

// Called every frame
void ABaseGeomeryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
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

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
	}

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


void ABaseGeomeryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
		case EMovementType::Sin:
		{
			FVector CurrentLocation = GetActorLocation();

			if (GetWorld())
			{
				float Time = GetWorld()->GetTimeSeconds();

				CurrentLocation.Z = InitialLocation.Z + GeometryData.amplitude * FMath::Sin(GeometryData.Frequency * Time);
				SetActorLocation(CurrentLocation);
			}
			break;
		}

		case EMovementType::Static: break;
		default: break;
	}
}

void ABaseGeomeryActor::SetColor(const FLinearColor &Color)
{
	if (!BaseMesh) return;


	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeomeryActor::OnTimerFired()
{
	if (++TimerCount <= MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();

		UE_LOG(LogTemp, Display, TEXT("TimerCount: %i, Color to set is: %s"), TimerCount, *NewColor.ToString());
		SetColor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Timer has been stopped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}

}

