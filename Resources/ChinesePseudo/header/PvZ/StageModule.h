//
//  StageModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StageModule_h
#define PlantsVersusZombies2_StageModule_h

#include "LevelModule.h"
#include "PVZTypes.h"
#include "WaveGenerator.h"
#include "BoardEnums.h"
#include "Board.h"
#include "Wave.h"

enum StageMusicState
{
	STAGEMUSIC_NotStarted,
	STAGEMUSIC_Initial,
	STAGEMUSIC_GameStart,
	STAGEMUSIC_HugeWave1,
	STAGEMUSIC_HugeWave2,
	STAGEMUSIC_FinalWave,
	STAGEMUSIC_LoseGame,
	STAGEMUSIC_WinGame,
};

class StageModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(StageModule, LevelModule, RtClass);
    
    StageModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
	/// Accessors
    RtWeakPtr<PopAnim>		GetDirtSpawnEffect();
    GridItemTypePtr			GetGravestoneDefaultType();
    GridItemTypePtr			GetRailcartDefaultType();
	ImagePtr				GetGravestoneImage(int i_variation, int i_damageState);
	ZombieTypePtr			GetFlagZombieType();
	ZombieTypePtr			GetBasicZombieType();
	ZombieTypePtr			GetArmor1ZombieType();
	ZombieTypePtr			GetArmor2ZombieType();
	ZombieTypePtr			GetArmor4ZombieType();
    virtual ZombieTypePtr	GetZombieTypeForBasicHelm(HelmType i_helmType);
    virtual const ZombieTypePtr GetGargantuarForStage() const;
	EventType				GetZombieEventType();
	inline const int		GetBackgroundLeftImageWidth();
	inline const int		GetBackgroundMiddleImageWidth();
	inline const int		GetBackgroundRightImageWidth();

	ZombieTypePtr			ResolveZombieType(const std::string& i_genericTypeName);
	
    void					PlayZombieEventAudio();
	
	const std::string&		GetStagePrefix() const;
	
    void					SetMusicTriggerOverride(const std::string& i_override);
    bool					GetShouldStopMusic() { return m_shouldStopMusic; }
    bool					GetShouldStartMusic() { return m_shouldStartMusic; }
    void					SetShouldStopMusic(bool i_shouldStop) { m_shouldStopMusic = i_shouldStop; }
    void					SetShouldStartMusic(bool i_shouldStart) { m_shouldStartMusic = i_shouldStart; }
    void					SetSuppressMusicStateChangeEvents(bool i_suppress) { m_suppressMusicStateChangeEvents = i_suppress; }
	void					SetDefaultZombieSpawnPositionXOffset(int i_offset) { m_zombieSpawnPositionXOffset = i_offset; }
    
    virtual void			StartMusic();
	
	/// Public Virtual StageModule interface
	virtual bool			CanGraveStoneSpawnAt(int i_gridX, int i_gridY)					{ return true; }
	virtual bool			CanZombieSpawnInRow(int i_row, ZombieTypePtr i_type)			{ return true; }
	virtual bool			UseToolAt(const std::string& i_toolName, int i_mouseX, int i_mouseY, int i_clickCount) { return false; }
	virtual int				GetPlantedPacketCount(const std::string& i_packetType) 			{ return 0; };
	virtual int				GetDefaultZombieSpawnPositionX(int i_row);
    
    bool MatchWorld(const std::string& i_world);
	/// Implemented LevelModule interface
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
	
	virtual void			onPostLoad() override;

	/// Protected StageModule interface
	// renderBackground
	//	- Override this if you want to draw additional elements *directly* on top of our backdrop
	//	- Rendered at RENDER_LAYER_UI_BOTTOM
	virtual void			renderBackground(Graphics* i_g);
    void                    renderBlackBars(Graphics* i_g);
    
	virtual void			onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to);
	virtual void			onLevelLoaded();

	void setStageMusicState(StageMusicState i_state);
	
	std::map<ZombieTypePtr, int> m_zombieTypeCounts;

	virtual void 			stopZombieGroans();

	std::string				getMusicTypeForCurrentLevel();
    
    void                    FlashDamage();
    bool                    InDamageFlash();
    Color                   GetDamageFlashColor();

private:
	/// Private methods + members
	void addBackgroundToRenderQueue(class RenderQueue* i_queue);
	void parseImages();
    void unregisterObservers();

    void startGameStartedMusic();
    void startHugeWaveMusic();
    void startFinalWaveMusic();
    void startLoseMusic();
    void startWinMusic();
    void startAmbientAudio();
    void stopMusic();
    void stopAmbientAudio();
    
    void onZombieAdded(class Zombie* i_zombie);
    void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);

    void onGamePaused();
    void onGameUnpaused();
    void onGameWon();
    void onGameLost();
    void onHugeWave();
    void onFinalWave();
    void onHugeWaveComing(bool i_isFinal, int i_wave);
    void onWaveStarted(int i_wave, WaveType::WaveType i_type, bool i_isFinal);

    void changeMusic(const int i_wave, const WaveType::WaveType i_type, const bool i_isFinal);
	
	/// Serialized
	// There are two huge wave events, we need to alternate between them
	bool m_sendAlternateHugeWaveEvent;
    std::string m_belongsToWorld = "";
    
	std::string m_musicTriggerOverride;
	/// Transient
	// Cached WeakPtr's to our background image assets
    ImagePtr m_backImage;
	ImagePtr m_backImageRight;
	ImagePtr m_backImageLeft;
	std::vector<std::vector<ImagePtr> > m_gravestoneImages;
	
	// Cached ZombieTypePtr's
	ZombieTypePtr m_flagZombieType;
	ZombieTypePtr m_basicZombieType;
	ZombieTypePtr m_armor1ZombieType;
	ZombieTypePtr m_armor2ZombieType;
	ZombieTypePtr m_armor4ZombieType;
	
	bool            m_shouldStopMusic;
	bool            m_shouldStartMusic;
	StageMusicState m_musicState;
    bool            m_suppressMusicStateChangeEvents;
    int             m_lastWaveIntroMusic;
    
    pvztime_t       m_damageFlashStartTime;
    bool            m_InDamageFlash;
    Color           m_damageFlashColor;
	int 			m_zombieSpawnPositionXOffset;
};

inline const int StageModule::GetBackgroundLeftImageWidth()
{
	if (m_backImageLeft)
	{
		return m_backImageLeft->GetWidth();
	}
	return 0;
}

inline const int StageModule::GetBackgroundMiddleImageWidth()
{
	if (m_backImage)
	{
		return m_backImage->GetWidth();
	}
	return 0;
}

inline const int StageModule::GetBackgroundRightImageWidth()
{
	if (m_backImageRight)
	{
		return m_backImageRight->GetWidth();
	}
	return 0;
}

class StageModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StageModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StageModule::StaticGetClass();
	}
	
	StageModuleProperties()
	{
		ZombieEventType = EVENTTYPE_NONE;
        ProgressFlagAsset = "IMAGE_UI_HUD_INGAME_PROGRESS_METER_FLAG_DEFAULT";
        RailcartDefaultTypeName = "railcart_cowboy";
        GravestoneDefaultTypeName = "gravestone_egypt";
        DirtSpawnEffectName = "POPANIM_EFFECTS_TOMB_DIRT";
        
        BackgroundImageLeft   = "TEXTURE_LEFT";
        BackgroundImageMiddle = "TEXTURE";
        BackgroundImageRight  = "TEXTURE_RIGHT";
        
		DrawBackgroundLeft = true;
		DrawBackgroundMiddle = true;
        DrawBackgroundRight = true;
	}
    
    std::string BelongsToWorld = "";
	
	std::string BackgroundImagePrefix;
    std::string BackgroundImageLeft;
    std::string BackgroundImageMiddle;
    std::string BackgroundImageRight;

	bool        DrawBackgroundLeft;
	bool        DrawBackgroundMiddle;
    bool        DrawBackgroundRight;
    
	std::vector<std::string> GravestoneImagePrefixes;
	
	std::string StagePrefix;
	
	std::string BasicZombieTypeName;
	std::string FlagZombieTypeName;
	std::string Armor1ZombieTypeName;
	std::string Armor2ZombieTypeName;
	std::string Armor4ZombieTypeName;
    std::string MusicSuffix; 
    std::string AmbientAudioSuffix;
    std::string RailcartDefaultTypeName;
    std::string GravestoneDefaultTypeName;
    std::string DirtSpawnEffectName;
    
	EventType	ZombieEventType;
    std::string ZombieEventAudio;

    std::vector<Point> DisabledStreetCells;
    std::string ProgressFlagAsset;

    std::vector<std::string> StarChallengeUnlockLevel;

    std::string LevelPowerupSet;
};

typedef RtWeakPtr<const StageModuleProperties> StageModulePropertiesPtr;


#endif
