// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_2017.h"
#include "MainHUD.h"
#include "VRGameModeBase.h"

AVRGameModeBase::AVRGameModeBase()
{
	// use our custom HUD class
	HUDClass = AMainHUD::StaticClass();
}


