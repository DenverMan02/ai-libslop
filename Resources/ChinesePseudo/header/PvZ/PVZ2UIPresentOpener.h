//

//  PVZ2UIPresentOpener.h

//  PlantsVersusZombies2

//

//  Created by jsola on 3/25/13.

//  Copyright (c) 2013 PopCap Games. All rights reserved.

//



#ifndef PlantsVersusZombies2_PVZ2UIPresentOpener_h

#define PlantsVersusZombies2_PVZ2UIPresentOpener_h

//PVZ2_CHINESE_BEGIN

#include "SexyAppFramework/Widget.h"

#include "SexyAppFramework/RtDb.h"



using namespace Sexy;

//PVZ2_CHINESE_END



#include "Widget.h"

#include "TimeMgr.h"



class PVZ2UIPresentWidget : public Sexy::Widget

{

public:

	PVZ2UIPresentWidget(class StandaloneEffect* i_contentsEffect, bool i_shiny);

	virtual ~PVZ2UIPresentWidget();

	

	void StartOpening();

	bool IsDoneOpening() const;

	

	virtual void Update();

	virtual void Draw(Sexy::Graphics* i_g);

	virtual void MouseDown(int x, int y, int theBtnNum, int theClickCount);

	

private:

	void showPrize();

	void onAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_param);

	

	class PopAnimRigRectDrawer* m_rigRectDrawer;

	class PopAnimRig* m_rig;

	

	class PopAnimRigRectDrawer* m_overlayRectDrawer;

	class PopAnimRig* m_overlayRig;

	

	class StandaloneEffect* m_contentsEffect;

	float m_contentsEffectOrigScale;

	bool m_startedOpening;

	bool m_prizeShown;

};



class PVZ2UIPresentOpener : public Sexy::Widget

{

public:

	PVZ2UIPresentOpener();

	virtual ~PVZ2UIPresentOpener();

	

	void AddPresent(RtWeakPtr<const class PresentTable> i_presentTable, RtWeakPtr<const class PresentType> i_present);

	//PVZ2_CHINESE_BEGIN

	void AddPresent(RtWeakPtr<const class PresentType> i_present);

	//PVZ2_CHINESE_END

	void OpenAllPresents();

	bool IsDoneOpening() const;



	virtual void Update();

	virtual void Draw(Sexy::Graphics* i_g);

	virtual void Resize(int, int, int, int);

	

private:

	Rect calcCardRect();

	void layoutWidgets();

	

	std::vector<PVZ2UIPresentWidget*> m_presentWidgets;

};



#endif

