#ifndef UISPACETIMEENERGY_H
#define UISPACETIMEENERGY_H

#include "core.h"
#include "RtObject.h"
#include "UIEasyButtonWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "PrimeTextWidget.h"
#include "Renderable.h"
#include "ButtonListener.h"
#include "AnimationMgr.h"
#include "AnimationControllerHelpers.h"
#include "PVZ2UIButton.h"
#include "TimeEnergyModule.h"
#include "DigitalNumberWidget.h"

///
/// Time Energy Hint Animation
///
class TimeEnergyAnimation : public AnimationController, public Renderable, public ButtonListener
{
public:
	enum {
		TimeEnergyAnimationButton = 1234
	};

	RT_CLASS_DEFINE(TimeEnergyAnimation, AnimationController, RtClass);

	static TimeEnergyAnimation* Create(pvztime_t i_duration, TimeEnergyTriggerType type){
		TimeEnergyAnimation* animation = GameObject::Create<TimeEnergyAnimation>(PVZDB::TABLE_GAMEOBJECTS);
		animation->Init(i_duration, type);
		return animation;
	}

	virtual void onDestroy() override;
    virtual void Draw(Sexy::Graphics* g) override;
	virtual void ButtonDepress(int i_buttonID) override;
	virtual void AddToRenderQueue(class RenderQueue* i_queue) override;

	void Init(pvztime_t i_duration, TimeEnergyTriggerType type);

protected:
	TimeEnergyTriggerType m_type;// animation type
	PVZ2UIButton* m_button;// fullscreen button
	Image* m_image;// time energy icon image
	SexyString m_descStr;// time energy desc
	int m_imageX;// image x
	int m_imageY;// image y
};

///
/// UISpacetimeEnergy
///
class UISpacetimeEnergy : public UIEasyButtonWidget
{
public:
	RT_CLASS_DEFINE(UISpacetimeEnergy, UIEasyButtonWidget, RtClass);
	
	UISpacetimeEnergy();
	virtual ~UISpacetimeEnergy();
	
	// Public Interface (Inheritable)
	
	virtual void				Draw(Graphics* i_g) override;
	virtual void				onUpdate() override;

	// Public Interface (Core)
	float GetCurrentProgressRatio() { return m_energy / m_maxEnergy; }
	
	void SetValueMax(float value);
	float GetMaxValue();

	void setCurrentEnergy(float i_energy) { m_energy = i_energy; }
	float getCurrentEnergy() { return m_energy; }

protected:
	// Protected Interface (Inheritable)
	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	
	virtual void				initLoadingResourcesGroupList() override;
	virtual void				registerForEvents() override;
	virtual void				unregisterForEvents() override;
	virtual void				onCollectableCollectionFinished(class Collectable* i_bankedCollectable);
	virtual void 				onLoadComplete() override;

	void TimeEnergyTrigger(int type);
	void InitSpiralEffect();
	void InitDigitalNumber();
	void InitEnergyRect();
	void UpdateDigitalNumber();
	void DrawDigitalNumber(Graphics* i_g, int x, int y);
	void UpdateEnergyImage(int ratio);
	void UpdateSpiralMachineImage();

private:
	float m_energy;
    float m_maxEnergy;
    bool m_showBlackHole;
    bool m_showWormHole;
    bool m_showPortal;
    Effect_PopAnim* m_spiralEffect;// spiral effect
    Image* m_energyImage;
    Rect m_energyRect;
//    DigitalNumberWidget* m_digitalNumber;

	int m_digitalNumCount;// the count of number
	std::vector<int> m_digitalNumberList;// put single number in list
	std::vector<ImagePtr> m_digitalNumberImages;// number images, according to 0 ~ 9
	int m_itemWidth;// digital number width
	int m_itemHeight;// digital number height

	int m_prevNumberRatio;// prev number ratio
	int m_spiralMachineCount;// draw spiral machine image
	Image* m_spiralMachineImage;
};

#endif //__COINBANK_H__
