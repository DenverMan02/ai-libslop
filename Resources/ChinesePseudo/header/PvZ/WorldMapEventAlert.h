//
//  WorldMapEventAlert.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 3/18/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMapEventAlert__
#define __PlantsVersusZombies2__WorldMapEventAlert__

#include "Precompile.h"
#include "MapPopupDialog.h"
#include "PVZ2UIDialog.h"
#include "TodStringFile.h"

class WorldMapEventAlert : public MapPopupDialog
{
public:
    
    enum AlertType
	{
        WMEA_DIALOG_OTHER_WORLD,
		WMEA_DIALOG_YETI_LEVEL,
	};
    
    enum AlertState
    {
        WMEAS_BADGE,
        WMEAS_DIALOG
    };

	WorldMapEventAlert();
	virtual ~WorldMapEventAlert();
    
    virtual void				PopIn();
    virtual void				PopOut();
	virtual void				Draw(Graphics* i_g);
    virtual void				DrawFromMap(Graphics* i_g, WorldMapCamera* i_camera = NULL,int index=-1);
    virtual void				SetAnchorLocation(const Point i_location);
    virtual void				OnMouseUp(const int i_mouseX, const int i_mouseY);

    void						Update();
    void                        ShowBadge();
    void                        HideBadge();

    inline void                 SetEvent(const MapEventItem* i_event);
    inline const MapEventItem*  GetEvent() const;
    
	inline void                 SetAlertType(const AlertType i_alertType);
    inline AlertType            GetAlertType() const;
    
    void                        SetPoppedInAnchorLocation(const Point i_location);
	Point                       GetAnchorLocation() { return m_anchorLocation;}
	
	void						SetScrollWidget(Widget* i_widget) {m_scrollWidget = i_widget;}
    
    bool                        IsVisibleInBounds(Rect i_bounds);
	
	bool						IsPoppedIn() {return m_alertState == WMEAS_DIALOG;}
    
protected:
	
    void						calculateLocation();
	void						calculateBadgeLocation();
    
    AlertState					m_alertState;
    bool                        m_needBuyYeti;
    int                         m_yetiCoin;
    AlertType					m_alertType;
    PopAnimRig*					m_badgeAnimRig;
    
private:

    void						drawAlertBadge(Sexy::Graphics* i_g);
    void						drawDialog(Sexy::Graphics* i_g);
    void						drawOtherWorldDialog(Sexy::Graphics* i_g);
    void						drawYetiLevelDialog(Sexy::Graphics* i_g);

    void						setState(AlertState i_state);
    void						setupBadgeState();
    void						setupDialogState();
    
    
    const MapEventItem*			m_event;

    Point						m_origAnchorLocation;
	Widget*						m_scrollWidget;
	int							m_scrollOffset;
};

inline void WorldMapEventAlert::SetEvent(const MapEventItem* i_event)
{
    m_event = i_event;
}

inline const MapEventItem* WorldMapEventAlert::GetEvent() const
{
    return m_event;
}

inline void WorldMapEventAlert::SetAlertType(const AlertType i_alertType)
{
    m_alertType = i_alertType;
}

inline WorldMapEventAlert::AlertType WorldMapEventAlert::GetAlertType() const
{
    return m_alertType;
}

#endif /* defined(__PlantsVersusZombies2__WorldMapEventAlert__) */
