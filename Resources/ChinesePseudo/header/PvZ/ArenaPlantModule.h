/*
 * ArenaPlantModule.h
 *
 *  Created on: 2015-9-24
 *      Author: jianglc
 */

#ifndef ARENAPLANTMODULE_H_
#define ARENAPLANTMODULE_H_

#include "StandardLevelIntro.h"
#include "Core.h"
#include "ButtonListener.h"
#include "GameNotify.h"
#include "PVZTypes.h"
#include "ArenaInfo.h"
#include "ArenaPrecompile.h"
#include "AnimationMgr.h"

enum ArenaPlantType
{
    TYPE_1,
    TYPE_2,
    TYPE_3,
    TYPE_TUTORIAL,
    TYPE_TUTORIAL_ATTACK,
    TYPE_COUNT
};

class BouncingArrow;

class ArenaPlantModule : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(ArenaPlantModule, StandardLevelIntro, RtClass);

protected:
	ArenaPlantModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    virtual void initializeModule() override;
	virtual void registerForEvents() override;
    virtual bool isConsumableInstantPlant(PlantTypePtr i_plantTypePtr);
    virtual bool suppressReadySetGo() const override { return true; }
    
    void					addToRenderQueue(class RenderQueue* i_queue);

	//void onViewBoardOrZombiesButtonPressed();
	void                    onStartGameButtonPressed();
    void					onPlantPlanted(class Plant* i_plant);
    void					onCursorAdded(class BaseCursor* i_cursor);
    void					onCursorDestroyed(class BaseCursor* i_cursor);

	enum State
	{
		PVZ_BEGIN_ENUM(STATE_ARENA_),
		STATE_ARENA_START,
		STATE_ARENA_INTRO,
		STATE_ARENA_START_PLANTING,
		STATE_ARENA_PLANTING,
		STATE_ARENA_FINISH_PLANTING,
		PVZ_END_ENUM(STATE_ARENA_),
	};
    
    enum TutorialState
    {
        PVZ_BEGIN_ENUM(TUTORIALSTATE_),
        TUTORIALSTATE_ADVICE_1,
        TUTORIALSTATE_CHOOSE_PLANT1,
        TUTORIALSTATE_PLACE_PLANT1,
        TUTORIALSTATE_CHOOSE_PLANT2,
        TUTORIALSTATE_PLACE_PLANT2,
        TUTORIALSTATE_CHOOSE_PLANT3,
        TUTORIALSTATE_PLACE_PLANT3,
        TUTORIALSTATE_CHOOSE_PLANT4,
        TUTORIALSTATE_PLACE_PLANT4,
        TUTORIALSTATE_CHOOSE_PLANT5,
        TUTORIALSTATE_PLACE_PLANT5,
        TUTORIALSTATE_SAVE,
        PVZ_END_ENUM(TUTORIALSTATE_),
    };

public:
    bool isFinishPlanting(){return m_arenaPlantState == STATE_ARENA_FINISH_PLANTING;}

    float calcGoalX();
    
    void SetType(ArenaPlantType i_type) {m_type = i_type;}
    
    bool isStartPlanting() { return m_arenaPlantState == STATE_ARENA_PLANTING; }

private:

	virtual void bringUpSeedChooser() override;

    bool preventSave();

	void onLoadComplete() override;
	void startIntro();
    void onEndLevel();
	void onUpdate();
	void onGameplayStarted();
    
    void onSaveDialogOK();
    void onSaveDialogCancel();
    void onTimeOutOk();
    void onPingSuccess(bool timeout);
	//void onEndLevel();
	//void onViewZombiesComplete();

	void setState(State i_state);

	void setToolsState(const bool i_introState);
    
    void setToolsVisible(bool i_visible);

	ArenaPlantInfos StoredPlantInfos();
    
    void StorePVPPlantPosition();
    void StorePVPPlantInfo();
    void RequestPVPSave();
    
    void onSavePVPPlayerInfo(bool i_success, int i_errorCode);
    void OnCloseDialog();
    void onNetworkError(int erroId);
    
    void initPlayerInfo();
    
    void createBrains();
    PopAnim*    getMowerAnim();
    const std::string& getMowerAudio();
    void        onReadyForBrains();
    
    void onNotifySwitchPlant(Plant* i_originPlant, int i_gridX, int i_gridY);

	State m_arenaPlantState;
	pvztime_t m_stateEntryTime;
    ArenaPlantType m_type;
    ArenaType m_arenaType;
    
    //add for tutorial
    AnimationMgrWkPtr                   m_animationMgr;
    RtWeakPtr<BouncingArrow>            m_bouncingArrow;
    TutorialState m_tutorialstate;
    bool  m_doTutorialBattle;
    bool  m_saveSuccess;
    pvztime_t m_nextPing;
    
    bool                                m_isTutorialFingerActive;
    bool                                m_isTutorialFingerResting;
    pvztime_t                           m_tutorialFingerFlyTime;
    pvztime_t                           m_tutorialFingerRestTime;
    RtWeakPtr<class Effect_PopAnim>     m_handEffect;
    float                               m_tutorialFingerPosX;
    float                               m_tutorialFingerPosY;
    class PVZ2UIDialog*                 m_timeoutDialog = nullptr;
    
    void  setTutorialState(TutorialState tState);
    void  onAdvice1Finish();
    void  onTutorialBattle();
    
    void            startCurvingTutorialFinger();
    void            updateCurvingTutorialFinger(float i_startX, float i_startY, float i_endX, float i_endY, pvztime_t i_duration);
    void            stopCurvingTutorialFinger();
};

class ArenaPlantProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(ArenaPlantProperties, StandardLevelIntroProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return ArenaPlantModule::StaticGetClass();
	}

	ArenaPlantProperties()
	{
		StartingSun = 0;
        PlantDistance = 0;
        MowerEntryAnimDuration = 2.5f;
	}

	int StartingSun;
	int PlantDistance;
    float			MowerEntryAnimDuration;
    std::string 	MowerPopAnim;
    std::string 	MowerActivatedAudioEvent;
};

#endif /* ARENAPLANTMODULE_H_ */
