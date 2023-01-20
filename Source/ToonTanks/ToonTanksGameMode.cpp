// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if(ATower* DamagedTower = Cast<ATower>(DeadActor))
    {
        DamagedTower->HandleDestruction();
        TargetTower--;
        if(TargetTower==0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();      
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTower = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();
    if(ToonTanksPlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("Handle Game start called"));
        ToonTanksPlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, startDelay, false);
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    UE_LOG(LogTemp, Warning, TEXT("Avai Towers: %d"), Towers.Num());
    return Towers.Num();
}