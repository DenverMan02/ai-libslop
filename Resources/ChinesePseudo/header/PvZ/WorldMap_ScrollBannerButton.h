/*
 * WorldMap_ScrollBannerButton.h
 *
 *  Created on: 2021-4-9
 *      Author: zhousen
 */

#ifndef WORLDMAP_SCROLLBANNERBUTTON_H_
#define WORLDMAP_SCROLLBANNERBUTTON_H_

class UIScrollWidgetComponent;

namespace Message
{
    void ShowScrollBanner(bool show);
}

////////////////////////////////
///  Scroll Banner Data
////////////////////////////////
struct S2C_ScrollBannerData
{
    int m_activityID;// activity id
    int m_activityType;// activity tyep (eg. festival event or 7 guides)
    S2C_ScrollBannerData()
    {
        m_activityID = 0;
        m_activityType = 0;
    }
};

class S2C_ScrollBannerNetworkData : public INetworkData
{
public:
    RT_CLASS_DEFINE(S2C_ScrollBannerNetworkData, INetworkData, RtClass);
    std::vector<S2C_ScrollBannerData> BannerList;
};

class WorldMap_ScrollBannerButton : public UIScrollWidgetComponent
{
public:
    WorldMap_ScrollBannerButton();
    virtual ~WorldMap_ScrollBannerButton();

    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void InitView(S2C_ScrollBannerNetworkData data);
    void RequestNetwork();
    void Test();
    void ShowScrollBanner(bool show);
    bool HasBanner() { return _hasBanner; }
    bool CheckVisibility();
    void OnOrientationChanged();

protected:
    bool _hasBanner;// check if has banner
    std::vector<int> _activityIDList;// current activity id list
};

#endif /* WORLDMAP_SCROLLBANNERBUTTON_H_ */
