#ifndef NostalgiaPVZGameView_h
#define NostalgiaPVZGameView_h

#include "UISingletonDialog.h"
#include "UIListener.h"
#include "UIScrollWidget.h"
#include "Image.h"
#include "UIUtil.h"
#include "NetworkData.h"
#include "PolygonCheckWidget.h"

class NostalgiaPVZGameView : public Sexy::Widget
{
public:
	NostalgiaPVZGameView();
	virtual ~NostalgiaPVZGameView();
	
	virtual void Draw(Sexy::Graphics* i_g) override; 

    void InitView();
    void TriggerTutorial();
private:
	class NostalgiaMainView* m_mainView;
};

class NostalgiaMainView : public PolygonCheckWidget
{
public:
	NostalgiaMainView();
	virtual ~NostalgiaMainView();
	
	virtual void Update() override;
	virtual void Draw(Sexy::Graphics* i_g) override; 
	void InitView();

	virtual void onTouchBegan(int i_id) override;
    virtual void onTouchMoved(int i_id) override;
    virtual void onTouchEnded(int i_id) override;

	void PolygonDepress(int i_id);

	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
private:
	SexyString m_userName;
	Color m_nameColor;
	SexyString m_timeCountDown;
	SexyString m_timeReset;
	time_t m_timeCountDownEnd;
	time_t m_timeResetEnd;
	bool m_hardUnlocked;
	bool m_thisRequested;
};

#endif
