#ifndef _COLLECTIONUI_H_
#define _COLLECTIONUI_H_

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "Effect_BouncingArrow.h"
#include "MagentoService.h"	//PVZ2_CHINESE_START
#include "Effect_PopAnim.h"


class CollectionUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(CollectionUI, UIWidget, RtClass);
	
	CollectionUI();
	virtual ~CollectionUI();

    void Draw(Sexy::Graphics *i_g) override;

	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

	void onLevelStarting();
	void onLastStandStart();
private:
	int m_rare;
	bool m_hasCollection;
};

#endif