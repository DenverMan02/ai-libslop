//
//  MoldColonyChallenge.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/22/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MoldColonyChallenge__
#define __PlantsVersusZombies2__MoldColonyChallenge__

#include <string>
#include <vector>

#include "ChallengeModule.h"
#include "LevelModule.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyAppFramework/Common.h"
#include "SexyString.h"
#include "TodCommon.h"
#include "TodStringFile.h"
#include "BoardEnums.h"

class BoardEntity;
class BoardGridMapProps;
class Effect_PopAnim;
class StandaloneEffect;

class MoldColonyChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(MoldColonyChallenge, Challenge, RtClass);

	void registerForEvents() override;

    MoldColonyChallenge()
	: m_moldState(MS_Idle)
	{}

private:
	void onFail() override;

	enum MoldState
	{
		MS_Idle,
		MS_Cowering,
		MS_Dead,
	};

	void levelStarted();
	void addMold(int i_row, int i_col);
	void addNormalMold(int i_row, int i_col);
	void addRailcartMold(int i_row, int i_col);
	
	void levelEnded();
	
	void winOutroStarted();
	
	void gameplayUpdate();
	bool isCursorAboveMold();
	
	void gameplayEnded();

	void gatherPlantingRestrictions(const Sexy::Point &i_gridPosition, const class PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons);

	void playMoldAnimation(const std::string &i_animName, bool i_looping);

	void onRailcartMoved(class GridItemRailcart* i_railcart);
	void onAnimStopped(StandaloneEffect* i_effect);

	MoldState m_moldState;
	std::vector<RtWeakPtr<Effect_PopAnim> > m_mold;

	// Mold bound to objects (like railcarts)
	struct BoundMold
	{
		RtWeakPtr<BoardEntity> Owner;
		RtWeakPtr<Effect_PopAnim> Mold;
	};
	std::vector<BoundMold> m_boundMold;
};

class MoldColonyChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(MoldColonyChallengeProps, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return MoldColonyChallenge::StaticGetClass();
	}

	SexyString GetDescription() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANT_BEFORE_LINE]"));
	}

	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANT_BEFORE_LINE_NAME]"));
	}
	
	RtWeakPtr<BoardGridMapProps> Locations;
};

#endif /* defined(__PlantsVersusZombies2__MoldColonyChallenge__) */
