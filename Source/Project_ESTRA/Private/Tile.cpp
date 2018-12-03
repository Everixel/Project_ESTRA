// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tile.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	boxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	RootComponent = boxTrigger;
	boxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnOverlapBegin);
	boxTrigger->OnComponentEndOverlap.AddDynamic(this, &ATile::OnOverlapEnd);

}

void ATile::OnOverlapBegin_Implementation(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//if (GEngine) {
		if (OtherActor) {
			if (OtherActor->GetClass() == redTeamCharacterClass)
			{
				redTeamCountInsideTile++;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Red character entered tile trigger!"));
			}
			else if (OtherActor->GetClass() == blueTeamCharacterClass)
			{
				blueTeamCountInsideTile++;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Blue character entered tile trigger!"));
			}

			if (GetTotalCountOfCharactersInTile() > 0) {
				StartCaptureProcess();
			}
		}
	//}
}

void ATile::OnOverlapEnd_Implementation(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//if (GEngine) {
		if (OtherActor) {
			if (OtherActor->GetClass() == redTeamCharacterClass)
			{
				redTeamCountInsideTile--;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Character outside trigger!"));
			}
			else if (OtherActor->GetClass() == blueTeamCharacterClass)
			{
				blueTeamCountInsideTile--;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Character outside trigger!"));
			}

			if (GetTotalCountOfCharactersInTile() == 0) {
				StopCaptureProcess();
			}
		}
	//}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::ProcessCapture_Implementation()
{
	if (processingCapture) {

		UWorld* world = GetWorld();
		if (world)
		{
			if (redTeamCountInsideTile > blueTeamCountInsideTile)
			{
				if(team != ETeam::RED)
				{
					float delta = FApp::GetDeltaTime();
					if (redTeamCaptureProgress >= redTeamCaptureTarget)
					{
						redTeamCaptureProgress = redTeamCaptureTarget;
						blueTeamCaptureProgress = 0.f;
						team = ETeam::RED;
						redTeamCanBuild = true;
						blueTeamCanBuild = false;
					}
					else {
						float halfOffset = ((redTeamCountInsideTile - blueTeamCountInsideTile) * tileCaptureSpeed * delta) * 0.5f;
						if (blueTeamCaptureProgress > 0.f) {
							redTeamCaptureProgress += halfOffset;
							blueTeamCaptureProgress -= halfOffset;
						}
						else {
							redTeamCaptureProgress += halfOffset * 2.f;
							blueTeamCaptureProgress = 0.f;
						}
					}
				}
			}
			else if(blueTeamCountInsideTile > redTeamCountInsideTile)
			{
				if (team != ETeam::BLUE)
				{
					float delta = FApp::GetDeltaTime();
					if (blueTeamCaptureProgress >= blueTeamCaptureTarget)
					{
						blueTeamCaptureProgress = blueTeamCaptureTarget;
						redTeamCaptureProgress = 0.f;
						team = ETeam::BLUE;
						blueTeamCanBuild = true;
						redTeamCanBuild = false;
					}
					else {
						float halfOffset = ((blueTeamCountInsideTile - redTeamCountInsideTile) * tileCaptureSpeed * delta) * 0.5f;
						if (redTeamCaptureProgress > 0.f) {
							blueTeamCaptureProgress += halfOffset;
							redTeamCaptureProgress -= halfOffset;
						}
						else {
							blueTeamCaptureProgress += halfOffset * 2.f;
							redTeamCaptureProgress = 0.f;
						}
					}
				}
			}
			world->GetTimerManager().SetTimer(captureTimerHandle, this, &ATile::ProcessCapture, 0.000001f, false);
		}
	}
}

void ATile::StartCaptureProcess_Implementation() {
	
	if (!processingCapture) {
		processingCapture = true;
		ProcessCapture();
	}
}

void ATile::StopCaptureProcess_Implementation() {
	
	if (processingCapture) {
		processingCapture = false;
	}
}

bool ATile::IsCaptureInProgress_Implementation() {
	return processingCapture;
}

//============================
int32 ATile::GetTotalCountOfCharactersInTile_Implementation() {

	return redTeamCountInsideTile + blueTeamCountInsideTile;
}

