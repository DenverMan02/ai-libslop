
#ifndef WorldMap_MarqueeView_h
#define WorldMap_MarqueeView_h

#include "Widget.h"
#include "UIListener.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include <deque>

struct MarqueeViewItemData
{
    std::string PlayerName;
    std::vector<S2C_BonusInfo> BonusInfo;
};

class MarqueeViewData : public INetworkData
{
public:
	RT_CLASS_DEFINE(MarqueeViewData, INetworkData, RtClass);

    std::vector<MarqueeViewItemData> DataList;
};

class WorldMap_MarqueeView : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
public:
    RT_CLASS_DEFINE(WorldMap_MarqueeView, Sexy::Widget, RtClass);
    
    WorldMap_MarqueeView();
    virtual ~WorldMap_MarqueeView();
    
    virtual void Draw(Graphics* i_g) override;
    virtual void Update() override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void RequestNetwork();

protected:
    void OnOrientationChanged();

private:
    int m_index;

    Widget* m_container;
    int m_transMove;
    pvztime_t m_startMove;
    std::deque<int> m_record;
private:
    SexyString m_cacheData;
    pvztime_t m_changeTimer;
    pvztime_t m_displayTimer;
public:
    float m_speed;
};

class MarqueeViewManager : public LazySingleton<MarqueeViewManager>
{
public:
    void RequestMarqueeData();
    void ConstructDataInfo(std::deque<SexyString>& i_deque);
    void ConstructDataInfo(std::vector<SexyString>& i_vector);
    void PopFront();

    bool m_requested = false;
    std::deque<MarqueeViewItemData> m_cacheList;
};


#endif
