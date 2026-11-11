//
//  PinataManager.h
//  PlantsVersusZombies2
//
//  Created by Matt Westhoff on 10/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PinataManager__
#define __PlantsVersusZombies2__PinataManager__

#include <string>
#include <vector>

#include "PinataRewardDrawer.h"
#include "Point.h"
#include "PopAnimRig.h"
#include "ResourceHelpers.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "LevelOfTheDayConfigInfo.h"

class PopAnimRigRectDrawer;
class PinataStyleChooser;

namespace Sexy
{
	class Graphics;
}

class Pinata
{
public:
    
    Pinata();
    ~Pinata();
    
	int X;
	int Y;
	bool ShouldDraw;
	PopAnimRigRectDrawer* Drawer;
	PinataRewardDrawer RewardDrawer;
	PinataStyleChooser* StyleChooser;
	
	void Draw(Sexy::Graphics* i_g);
	void Update(pvztime_t i_t, pvztime_t i_dt);
	bool IsPopped() const;
	bool IsRevealing() const;
	bool IsRevealed() const;
	bool IsDropped() const;
	const TheDayRewardItem* GetReward() const;
    void Drop();
	void Pop(PopAnimRig::AnimStoppedDelegate i_onAnimStopped, const TheDayRewardItem* i_reward);
	void RevealPrize(const TheDayRewardItem* i_reward);
	
	void OnDropComplete(const std::string& i_animLabel);
	
private:
	pvztime_t m_elapsedTimeRevealing;
	pvztime_t m_StartFadeTime;
	pvztime_t m_EndFadeTime;
	bool m_isPopped;
	bool m_isRevealing;
	bool m_isDropped;
	const TheDayRewardItem* m_reward;
	float m_poppedTime;
	
};

class PinataManager
{
public:
	PinataManager();
	virtual ~PinataManager();
	
	void SetupPinatas(int i_parentWidth, Sexy::Delegate0 i_onAllPinatasOpened);
	std::vector<Pinata>& GetPinatas();
	void GetPinatasToDraw(std::vector<Pinata*>& o_pinatasToDraw);
	void DropPinatas(int i_numberOfPinatasToStartDropping);
	const Pinata* PopPinata(const Sexy::Point& location);
	void RevealAllPinataPrizes();
	bool AreAllPrizesRevealed();
	void SetPinataStyleChooser(PinataStyleChooser* i_chooser);
    int  GetOpenedPinatasCount() { return m_openedPinatas; }
    bool IsLocationValid(const Sexy::Point& spt);
    void SetRewardItem(const TheDayRewardItem* i_item);
    
    void RecvReward();

protected:
	virtual void rewardShown(const TheDayRewardItem* i_reward) {}
    virtual PopAnimRigRectDrawer* createPinataPopAnimRigDrawer(std::string strPinataArt);
	virtual Pinata* SelectUnPoppedPinataAtRandom();
	
	std::vector<const TheDayRewardItem*> m_rewards;
	std::vector<const TheDayRewardItem*> m_displayRewards;
	
private:
	void onExplodeFinished(const std::string& i_animLabel);
	void onAnimationFinished(const std::string& i_animLabel);
    
    void InitRewardList();

	std::vector<Pinata> m_pinatas;
	int m_openedPinatas;
	Sexy::Delegate0 m_onAllPinatasOpened;
	Sexy::Point m_boardTopLeft;
	bool m_prizesRevealing;
	PinataStyleChooser* m_pinataStyleChooser;
    bool m_bOpenFinished;
};

#endif /* defined(__PlantsVersusZombies2__PinataManager__) */
