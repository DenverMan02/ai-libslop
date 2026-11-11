//
//  MiniGameDialogAdaptor.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 6/17/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MiniGameDialogAdaptor__
#define __PlantsVersusZombies2__MiniGameDialogAdaptor__

#include "ArcadeMenuDialog.h"
#include "ArcadePropertySheet.h"
#include "SequentialActionRunner.h"

class ArcadePowerUpTemplateAdaptor;
class HotUIAnim;
class MiniGameDialogAdaptor;
class MiniGameLevelPackSublayoutAdaptor;

class UnlockAnimationAction : public RunnableAction
{
public:
	UnlockAnimationAction(RtWeakPtr<HotUIAnim> i_anim, const std::string& i_unlockAnimLabel, const std::string& i_idleAnimLabel, const std::string& i_audioEvent = "");
	void onBegin() override;
	
private:
	void onAnimFinished(const std::string& i_animLabel);
	
	RtWeakPtr<HotUIAnim> m_anim;
	std::string m_unlockAnimLabel;
	std::string m_idleAnimLabel;
	std::string m_audioEvent;
};

class MiniGameDialogAdaptor : public ArcadeMenuDialog
{
public:
	RT_CLASS_DEFINE(MiniGameDialogAdaptor, ArcadeMenuDialog, Sexy::RtClass);
	
	enum ButtonID
	{
		Close,
		EndlessMode,
		PowerUpFocus,
	};
	
	MiniGameDialogAdaptor();
	virtual ~MiniGameDialogAdaptor();
	
	void				ConfigureForMiniGame(const ArcadePropertySheetHelpers::ArcadeMode& i_miniGameType);
	void				RefreshUnlockStatus() override;
	void				PlayUnlockingAnimations();
	ArcadeMenuDialog*	Clone() const override;
	void				Update() override;
	
	const ArcadePropertySheetHelpers::ArcadeMode& GetArcadeModeProperties() const { return m_miniGameTypeProperties; }
	
	#pragma mark		- Button Handling
	void		OnPlayButtonPressed(const std::string& i_levelName);
	bool		OnBackButtonPressed() override;
	void		ButtonPress(int i_buttonID) override;
	void		ButtonDepress(int i_buttonID) override;
protected:
	
	#pragma mark		- UI View Link Handling
	void		onLoadUIView() override;
	void		onLinkToUIViewCreated() override;
	void		onLayoutFinished() override;
	
private:
	void			closeActivityCollection();
	void			close();
	std::string		getEndlessButtonLabel();
	std::string		getEndlessRecordLabel();
	
	HotUIAnim*		getEndlessButtonAnim() const;
	HotUIAnim*		getGiftBoxAnim() const;
	HotUIAnim*		getLevelButtonAnimByLevelID(const std::string& i_levelID) const;
	MiniGameLevelPackSublayoutAdaptor*	getLevelPackSublayoutByPackID(const std::string& i_packID) const;
	ArcadePowerUpTemplateAdaptor*		getPowerUpTemplateByPowerUpID(const std::string& i_collectionID, const std::string& i_powerUpID) const;
	
	ArcadePropertySheetHelpers::ArcadeMode m_miniGameTypeProperties;
	std::vector<HotUIAdaptor*> m_sublayouts;
	ForeverSequentialActionRunner m_actionRunner;
};

#endif /* defined(__PlantsVersusZombies2__MiniGameDialogAdaptor__) */
