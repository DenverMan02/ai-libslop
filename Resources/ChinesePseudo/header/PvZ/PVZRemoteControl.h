//
//  PVZRemoteControl.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/24/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PVZRemoteControl_H__
#define __PVZRemoteControl_H__

#include "Precompile.h"
#include "RtObject.h"


class PVZRemoteControl : public RtObject
{
public:
	RT_CLASS_DEFINE(PVZRemoteControl, RtObject, RtClass);
	
	/// ----------
	/// Properties
	
	// General purpose game control methods
	
	static bool GetPaused();
	static void SetPaused(bool i_paused);
	
	static bool GetEasyPlantingMode();
	static void SetEasyPlantingMode(bool i_enabled);
    
    /// --------
	/// Commands
    std::string TogglePause();
    std::string ToggleWavePause();
    std::string ToggleEasyPlanting();
    void ToggleFPSPig();
    void SetTimeScale(float i_scale);
    void ToggleHealthBars();
    void SetDebug(std::string& i_debugType);
    void Play();
    
    void AddCoins(int i_amt);
    void AddSunMoney(int i_amt);
    void AddStars(int i_amt);
    //Gives the specified seed packet type to the player, replacing one if their seedbank is full
    void GivePacket(std::string& i_packet);
    void PlantFoodAllPlants();
    
    std::string SpawnPlant(std::string& i_plantType, int i_col, int i_row);
    void SpawnAllPlants();
    void SpawnRandomPlants();
    void KillAllPlants();
    void ForceUnloadPlantType(std::string& i_plantType);
    
    std::string SpawnZombie(std::string& i_zombieType);
    std::string SpawnZombieAtRow(std::string& i_zombieType, int i_row);
    void SpawnAllZombies();
    void KillAllZombies();
    
    void NextWave();
    
    void LoadLevel(std::string& i_level);
    void EndLevel();
    void SetDate(const std::string& i_date);
    
    bool IsPlaying();
    void SetSkipNarration(bool i_status);
    void SetTestMode(bool i_mode);
    void StartLevel();
    void UnlockAllLevels();
    void ResetPlayer();
    void MainMenu();
    void ForceUnloadResourcesForZombie(std::string& i_zombieType);
    void SaveStateTo(std::string& i_profileName);
#ifdef HOST_ANDROID
    void LoadProfile(std::string& i_profileName);
#else
    void LoadProfile(const int i_profileId);
#endif
    void ReadOnlyMode(bool i_status);
    void RemoveMowers();
    std::string TogglePlantFoodMode();
    void SetDroppingSunPaused(bool i_status);
    void SetRecordingStrings(bool i_status);

    // RSB Patch Testing
    static void SetRsbUsed(const std::string& inRsbUsed);
    std::string GetRsbUsed();
    bool RsbPatchFileExists();
    bool ApplyRsbPatch();
    bool RemoveNewRsb();
    
private:
    static std::string mRsbUsed;
}; 

#endif
