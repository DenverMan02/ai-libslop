//
//  UITest.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _TimeTravelSelEntranceUI_h_
#define _TimeTravelSelEntranceUI_h_

#include "UISingletonDialog.h"
#include "WorldMapEditor.h"
#include "WorldMap.h"
class MapEventItem;

class TimeTravelSelEntranceUI : public UISingletonDialog<TimeTravelSelEntranceUI>
{
public:
	TimeTravelSelEntranceUI();
	virtual ~TimeTravelSelEntranceUI();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "TimeTravelSelEntranceUI"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;
    virtual void                DrawOverlay(Graphics* i_g) override;
    
    virtual void                Update() override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
    
    virtual void                TouchEnded( const Sexy::Touch& touch ) override;
    
    virtual void                GotFocus() override;

	int GetCurTimeTravelTDay() const;
private:
    void loadData();
	void drawMapPaths(Graphics* i_g);

	void rebuildMapPathGroups(WorldData* i_worldData);
	void purgeMapPathGroups();
	void SetMapPathAnimationState(MapPath* i_mapPath, const bool i_isUnlocked);
    SexyVector2 TransformPointFromCamera(float x, float y);

private:
	WorldMapCamera* m_camera;
	SexyVector2 m_cameraPosition;
	PopAnimRig* m_mapPathBeamOpen;
	PopAnimRig* m_mapPathUnlockPulse;
	std::vector<MapPathGroup> m_mapPathGroups;
	std::vector<MapRenderItem>		m_RenderList;
    std::vector<PopAnimRig*> m_popAnimRigs;
    std::vector<ImagePtr> m_worldImg;
	SexyString  m_timeToShow;
	Color m_timeColor;
    bool m_bDrawMap;
};


#endif
