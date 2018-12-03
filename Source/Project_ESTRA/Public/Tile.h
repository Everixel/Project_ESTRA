// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc.h"
#include "Tile.generated.h"

UCLASS()
class PROJECT_ESTRA_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	//This property can be used to set the possession of the tyle by either of the teams. It is "Neutral" by default.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	ETeam team = ETeam::NEUTRAL;

	// This property is editable in the editor and can be used to set the calss type of the red team characters. It is used internally and must be set to something (actor class by default).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UClass* redTeamCharacterClass = AActor::StaticClass();

	// This property is editable in the editor and can be used to set the calss type of the blue team characters. It is used internally and must be set to something (actor class by default).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UClass* blueTeamCharacterClass = AActor::StaticClass();

	// This property / component is the trigger (the tile itself). You can modify its propertis through the editor.
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxTrigger;

	// If the number of red and blue characters is the same nobody is progressing in capturing the tile.
	//This property shows the count of red team characters currently in the tile. This affects progress if this team has more than the opponent's (by design)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	int32 redTeamCountInsideTile = 0;

	//This property shows the count of blue team characters currently in the tile. This affects progress if this team has more than the opponent's (by design)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	int32 blueTeamCountInsideTile = 0;

	//These fields control which team/s can build in the tile. Be EXTRA careful if changing this manually as it may mess with the logic of various tile types.
	//This is a flag that controls of the red team can build in this tile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool redTeamCanBuild = true;

	//This is a flag that controls of the blue team can build in this tile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool blueTeamCanBuild = true;

	//This property shows the current progress that the red team has in capturing this tile. Increasing this reduces the enemy's progress (by design)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	float redTeamCaptureProgress = 0.f;

	//This property shows the current progress that the blue team has in capturing this tile. Increasing this reduces the enemy's progress (by design)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	float blueTeamCaptureProgress = 0.f;

	//These target properties need not be the same. They can be different. 
	//This property controls the target / goal of the red team. If the capture progress of this team reaches this target the team controls the tile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	float redTeamCaptureTarget = 100.f;

	//This property controls the target / goal of the blue team. If the capture progress of this team reaches this target the team controls the tile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	float blueTeamCaptureTarget = 100.f;

	//This property sets the speed at which a capturing happens. Defaults to 1.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	float tileCaptureSpeed = 1.f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//This is a timer that utilizes the process of capturing
	UPROPERTY(BlueprintReadOnly, Category = "Tile")
	FTimerHandle captureTimerHandle;

	//This is a flag that tells us if a capturing is currently happening
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	bool processingCapture = false;

	//This is the actual process of capturing - never use it directly - use StartCaptureProcess and StopCaptureProcess instead.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Capturing Process")
	void ProcessCapture();
	virtual void ProcessCapture_Implementation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//=============== Capturing Process ==============
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Capturing Process")
	void StartCaptureProcess();
	virtual void StartCaptureProcess_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Capturing Process")
	void StopCaptureProcess();
	virtual void StopCaptureProcess_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Capturing Process")
	bool IsCaptureInProgress();
	virtual bool IsCaptureInProgress_Implementation();

	//=============== Statistics ==============
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Statistics")
	int32 GetTotalCountOfCharactersInTile();
	virtual int32 GetTotalCountOfCharactersInTile_Implementation();
	
	//=============== Trigger ==============
	UFUNCTION(BlueprintNativeEvent, Category = "Trigger")
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Trigger")
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void OnOverlapEnd_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
