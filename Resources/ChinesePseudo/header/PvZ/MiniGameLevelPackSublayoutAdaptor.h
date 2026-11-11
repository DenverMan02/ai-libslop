//
//  MiniGameLevelPackSublayoutAdaptor.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/1/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MiniGameLevelPackSublayoutAdaptor__
#define __PlantsVersusZombies2__MiniGameLevelPackSublayoutAdaptor__

#include "HotUIAdaptor.h"
#include "ArcadePropertySheet.h"

class HotUIAnim;
class PowerUpUIButton;

class MiniGameLevelPackSublayoutAdaptor : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(MiniGameLevelPackSublayoutAdaptor, HotUIAdaptor, Sexy::RtClass);
	
	enum ButtonID
	{
		LevelOne,
		LevelTwo,
		LevelThree,
	};
	
	MiniGameLevelPackSublayoutAdaptor();
	virtual ~MiniGameLevelPackSublayoutAdaptor() {}
	void Configure(WidgetContainer* i_parent, const ArcadePropertySheetHelpers::ArcadeLevelPack& i_levelPackProps, Delegate1<const std::string&> i_onPlayDelegate);
	
	void RefreshUnlockStatus();
	bool IsPackComplete() const;
	bool IsConfiguredForPack(const std::string& i_packID) const;
	bool ContainsLevel(const std::string& i_levelID) const;
	HotUIAnim* GetLevelButtonAnimByLevelID(const std::string& i_levelID) const;
	PowerUpUIButton* GetPowerUpUIButton() const;
	
	#pragma mark - Button Handling
	void	ButtonPress(int i_buttonID) override;
	void	ButtonDepress(int i_buttonID) override;
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
private:
	void playLevel(const int& i_levelIndex);
	
	WidgetContainer* m_parent;
	ArcadePropertySheetHelpers::ArcadeLevelPack m_levelPackProps;
	Delegate1<const std::string&> m_onPlayDelegate;
};

#endif /* defined(__PlantsVersusZombies2__MiniGameLevelPackSublayoutAdaptor__) */
