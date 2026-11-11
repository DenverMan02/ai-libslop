/*
 * CommonUIManager.h
 *
 *  Created on: 2019-12-27
 *      Author: zhousen
 */

#ifndef COMMONUIMANAGER_H_
#define COMMONUIMANAGER_H_

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"
#include "UIDaveTreasure.h"


///
/// common bonus ui
///
class CommonBonusUI : public PopingWidget, public ButtonListener
{
public:
	CommonBonusUI();
    ~CommonBonusUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void InitView();
    void SetAward(const std::vector<LotteryBonus>& i_award);
    void SetChestAward(const std::vector<LotteryBonus>& i_award);
    Sexy::Image* GetRewardImage(int id);
    void SetSubmitDelegate(Delegate0 func) { m_submitFunc = func; }

private:
    void InitShiningAnims();

private:
    std::vector<LotteryBonus>           m_Award;
    std::vector<LotteryBonus>           m_ChestAward;
    bool                                m_IsDrawBonus;
    Rect                                m_bonusRect;
    Rect                                m_rewardRect;
    Rect                                m_titleImgRect;
    Rect                                m_titleRect;
    SexyString                          m_title;
    Rect                                m_submitRect;
    PVZ2UIButton*                       m_submit;
    Delegate0                           m_submitFunc;
    EffectAnim_UIAnim                   m_openAnimRig;
    EffectAnim_UIAnim                   m_backAnimRig;
};

///
/// common ui
///
class CommonUIManager : public LazySingleton<CommonUIManager>
{
public:
    CommonUIManager();
    ~CommonUIManager();
    
    void ShowBonus(const std::vector<LotteryBonus>& reward, const std::vector<LotteryBonus>& chestReward, Delegate0 func = {});
    void ShowBonusRedPachet(const std::vector<LotteryBonus>& reward);
    void CloseBonus();

    void ShowCheatingCheckWarning(int warningLevel);// cheating check
    void OnCheatingCheckCallback(class UIMessageBox* pBox, int buttonID);

protected:
    CommonBonusUI* _bonus;
};



#define gCommonUIManager CommonUIManager::GetInstance()


#endif /* COMMONUIMANAGER_H_ */
