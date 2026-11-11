#ifndef BoardHeroPlantButton_H_
#define BoardHeroPlantButton_H_

#include "UIEasyButtonWidget.h"
#include "Singleton.h"
#include "GameSubSystem.h"
#include "AnimationMgr.h"
#include "StandaloneEffect.h"
#include "Effect_PopAnim.h"
#include "PVZTypes.h"
#include "PlantType.h"
#include "HeroPlantConfig.h"
#include "HeroPlant.h"

enum BoardHeroPlantButtonState : int
{
    BHPS_None, //无状态
    BHPS_Prepare, //准备阶段
    BHPS_Ready, //条件满足，可以种植
    BHPS_Planted, //已种植，填充能量
    BHPS_PlantDied, //植物死亡，倒计时
};

//
// BoardHeroPlantButton
//
class BoardHeroPlantButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(BoardHeroPlantButton, UIEasyButtonWidget, RtClass);

    BoardHeroPlantButton();
    virtual ~BoardHeroPlantButton();

    virtual bool InitData( const std::string& i_plantName);

	virtual bool OnTouch(const Sexy::Touch& i_touch) override;
    virtual void Draw(Graphics* i_g) override;
    void OnClick();

    void SetHeroPlant(PlantPtr i_plantPtr);
    PlantPtr GetHeroPlant();

    void SetHeroButtonState(BoardHeroPlantButtonState i_state);
    BoardHeroPlantButtonState GetHeroButtonState() { return m_heroButtonState; }

protected:
    virtual void        onUpdate() override;
    virtual void        updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed) override;
    virtual void        onCursorDestroyed(class BaseCursor* i_cursor);
    virtual void        registerForEvents() override;
    virtual void        unregisterForEvents() override;

    bool CheckPlantRequirement();

    void DrawHightLight(Graphics* i_g);
    void DrawSwitchAnim(Graphics* i_g);
    void DrawNormal(Graphics* i_g);

protected:
    ImagePtr m_normalHeroPlantImg;
    ImagePtr m_pressedHeroPlantImg;

    class PopAnimRig* m_highlight = nullptr;
    class PopAnimRig* m_switch = nullptr;
    class PopAnimRig* m_lighting = nullptr;
    pvztime_t m_switchTimer;
    pvztime_t m_progressTimer;

    bool m_enablePlantfood;
    pvztime_t m_plantfoodTimer;
    pvztime_t m_respawnTimer;
    BoardHeroPlantButtonState m_heroButtonState;

    PlantPtr m_plant;
    PlantTypePtr m_plantType;
    HeroPlantPropsPtr m_heroProps;
private:
    bool m_plantfoodLog;
};

//
// BoardHeroPlantManager
//
class BoardHeroPlantManager : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(BoardHeroPlantManager, GameSubSystem, RtClass);

	virtual void Update() override;

    void InitialHeroPlantButton();

    int GetTotalSunCost();
    pvztime_t GetTimeConsumed();

    void ActivateHeroPlant(PlantPtr i_plant);
    PlantPtr GetHeroPlant();

    bool IsFirstPlant();
    void SaveHeroPlantInfo(const HeroPlantSaveInfo& i_info);
    void LoadHeroPlantInfo(HeroPlantSaveInfo& o_info);

    void IncreaseSunCost(int i_sun);

protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

private:
    int m_totalSunCost;
    int m_totalSunCostDisplay;
    int m_totalSunCostIncreaeStep;
    pvztime_t m_totalSunCostDisplayTimer;
    pvztime_t m_startTime;

    bool m_isFirstPlant;
    HeroPlantSaveInfo m_saveInfo;

    RtWeakPtr<BoardHeroPlantButton> m_boardButton;
};


#endif /* BoardHeroPlantButton_H_ */
