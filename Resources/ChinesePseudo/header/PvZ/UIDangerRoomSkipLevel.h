//
//  UIDangerRoomSkipLevel.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/11/10.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UIDangerRoomSkipLevel_h
#define UIDangerRoomSkipLevel_h

#include "UISingletonDialog.h"
#include "TimeMgr.h"
#include "NetworkData.h"

class UIWidgetAnim;

enum ButtonMode
{
	ButtonMode_Start,
	ButtonMode_Skip,
	ButtonMode_SkipLevelNextBoss,
};

class UIDangerRoomSkipLevel : public UISingletonDialog<UIDangerRoomSkipLevel>
{
public:
    UIDangerRoomSkipLevel();
    virtual ~UIDangerRoomSkipLevel();
    virtual bool							OnCreate() override;
    virtual std::string				GetLayoutName() override { return "DangerRoomSkipLevel"; }
    virtual void							Draw(Sexy::Graphics* i_g) override;
    
    // ButtonListener
    virtual void							ButtonDepress(int i_id) override;
    virtual void                         ButtonPress(int i_id) override;
    virtual void	Update() override;
    void SkipToLevel(int startLevel, int destLevel);
    void SetSun(int sun);
private:
    void DrawMower(Graphics* i_g, int x, int y, Image* image, bool disable);
    void DrawZombie(Graphics* i_g, int level);
    void OnSkipDangerRoom(int result, const class S2C_DangerRoomSkipLevel* data, const class S2C_PlayerInfo* pGemChanged);
    void InitSunWidget();
    void InitBeyondPlayer();
    void UpdateLevel();
    void UpdateMower();
    void UpdatePlantCount();
    void UpdateCurrentScore();
    void UpdateScorePredict();
    void UpdateBeyondPlayer();
    void PlaySelectEffect();
    void PlaySunAddEffect();
    void OnPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params);
    void DrawEffect(Sexy::Graphics* i_g, UIWidgetAnim* effect);
    UIWidgetAnim* CreateSelectEffect();
    Sexy::Image* GetMowerImage(const std::string& worldName);
    Point CalcCenterZombiePos();
    int GetZombieImageGap();
    bool InScrollLevel();
    void OnAnimStopped(const std::string &i_animLabelName);
    bool NeedChoosePlant();
    void OnSelectScreenClosed();

    void UpdateSkipLevelNextBossButton();
    int GetSkipLevelCount();
    void ShowEndlessBoost();

private:
    int m_offset = 0;
    int m_currentLevel = 0;
    int m_levelSkipTo = 0;
    int m_skipCount = 0;
    std::string m_world;
    Point m_zombieCenter;
    Sexy::Image* m_mowerImage = nullptr;
    UIWidgetAnim* m_selectEffectUp = nullptr;
    UIWidgetAnim* m_selectEffectDown = nullptr;
    UIWidgetAnim* m_sunEffect = nullptr;
    class NumberWidget* m_sunCount = nullptr;
    class NumberWidget* m_beyondPlayer = nullptr;
    const class DangerRoomPropertySheet* m_props = nullptr;
    pvztime_t m_time = 0;
    ButtonMode m_currentBtnMode = ButtonMode_Start;

    bool m_enableSkipLevelNextBoss;
};

class TrainingLevelItemWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	TrainingLevelItemWidget(int i_level);
    ~TrainingLevelItemWidget();
    virtual void        Draw(Sexy::Graphics* i_g) override;
    virtual void        Update() override;
    void                TouchBegan(const Sexy::Touch& i_touch) override;
    void 				TouchEnded(const Sexy::Touch& i_touch) override;
    // ButtonListener
    virtual void		ButtonDepress(int i_id) override;
    void InitLevel(const class DangerRoomPropertySheet* i_props, int i_currentPlayedLevel);
    void Select();

private:
    void OnNotifyLevelSelected(int i_id);
    void OnSelectOrUnselect(bool i_select);

    int m_currentLevel;
    Image* m_bgImg;
    Rect m_bgRect;
    Image* m_selectImg;
    Rect m_selectRect;
    bool m_gray;
    float m_scale;
    bool m_selected;
};

class New_S2C_DangerRoomTrainingInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_DangerRoomTrainingInfo, INetworkData, RtClass);

    int m_currentTrainingCount;
};

class UIDangerRoomTrainingSkipLevel : public UISingletonDialog<UIDangerRoomTrainingSkipLevel>
{
public:
	UIDangerRoomTrainingSkipLevel();
    virtual ~UIDangerRoomTrainingSkipLevel();
    virtual bool							OnCreate() override;
    virtual std::string				GetLayoutName() override { return "DangerRoomTrainingSkipLevel"; }
    virtual void							Draw(Sexy::Graphics* i_g) override;

    // ButtonListener
    virtual void							ButtonDepress(int i_id) override;
    virtual void                         ButtonPress(int i_id) override;
    virtual void	Update() override;
private:
    void OnSkipDangerRoom(int result, const class S2C_DangerRoomSkipLevel* data, const class S2C_PlayerInfo* pGemChanged);
    void OnPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params);
    void OnSelectScreenClosed();
    void OnNotifyLevelSelected(int i_id);
    void OnConfirmBack();
    void OnSelectClearTraining();
    void UpdateTrainingUI();
    void RequestStartTraining();
    void OnStartTraining();
    Image* GetWorldImage(const std::string& worldName);
private:
    int m_currentLevel = 0;
    int m_levelSkipTo = 0;
    int m_skipCount = 0;
    std::string m_world;
    const class DangerRoomPropertySheet* m_props = nullptr;
    pvztime_t m_time = 0;
    ButtonMode m_currentBtnMode = ButtonMode_Start;
    class UIScrollControl* m_pScrollLevels;
};

namespace Message
{
	void NotifyLevelSelected(int i_id);
}

#endif /* UIDangerRoomSkipLevel_h */
