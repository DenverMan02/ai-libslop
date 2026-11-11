//
//  DestroyGridItemsChallenge.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 6/21/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef DestroyGridItemsChallenge_h
#define DestroyGridItemsChallenge_h

#include "ChallengeModule.h"
#include "GridItem.h"
#include "LevelModule.h"
#include "RtDb.h"
#include "TodStringFile.h"
#include "UIWidget.h"

class DestroyGridItemsChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(DestroyGridItemsChallenge, Challenge, RtClass);
	
	void registerForEvents() override;
	
	DestroyGridItemsChallenge()
	{
		m_numGridItemsDestroyed = 0;
	}

	SexyString GetProgressDescription() const override;
	
private:
	void gameplayStarted();
	void gameplayEnded();
	
	void onGridItemDestroyed(const std::string& i_gridItemType);
	
	int m_numGridItemsDestroyed;
	RtWeakPtr<UIWidget> m_gridItemCounterWidget;
};

class DestroyGridItemsChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(DestroyGridItemsChallengeProps, LevelModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return DestroyGridItemsChallenge::StaticGetClass();
	}
	
	SexyString GetDescription() const override
	{
		SexyString gridItems = StrFormat(_S("%d"), GridItemsToDestroy);
		return TodReplaceString(StringToSexyString(ChallengeDescription), _S("{GRID_ITEMS}"), gridItems);
	}
	
	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[CHALLENGE_DESTROY_GRID_ITEMS_OF_TYPE_NAME]"));
	}
	
	DestroyGridItemsChallengeProps()
	: GridItemsToDestroy(0)
	, GridItemType("")
	, ChallengeDescription("")
	{}
	
	int GridItemsToDestroy;
	std::string GridItemType;
	std::string ChallengeDescription;
};

#endif /* DestroyGridItemsChallenge_h */
