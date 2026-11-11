//
//  DangerRoomLevelIntro.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 3/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomLevelIntro__
#define __PlantsVersusZombies2__DangerRoomLevelIntro__

#include "RtObject.h"
#include "StandardLevelIntro.h"

class DangerRoomLevelIntro: public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(DangerRoomLevelIntro, StandardLevelIntro, RtClass);
	
	DangerRoomLevelIntro();
	virtual ~DangerRoomLevelIntro();
	class DangerRoomStatScreen*		GetDangerRoomStatScreen();

protected:

	virtual void					registerForEvents() override;
	
	virtual bool					manualIntroStart() const override;
	virtual void					onStatScreenClosed();
	virtual void					startStandardIntro();
	
private:
	
	void							onLoadComplete() override;
	void							onLevelEnded();
	void							onUpdate();
	
	void							initStoredPlants(DangerRoomInfo& i_info);
    
    void                            OnDoDangerRoomNext();

	class DangerRoomStatScreen*		m_statScreen;
};

class DangerRoomLevelIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(DangerRoomLevelIntroProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return DangerRoomLevelIntro::StaticGetClass();
	}
};

namespace Message
{
	void DangerRoomReady();
}

#endif /* defined(__PlantsVersusZombies2__DangerRoomLevelIntro__) */
