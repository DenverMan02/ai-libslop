//
//  WorldMapEditor.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 11/25/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2_WorldMapEditor__
#define __PlantsVersusZombies2_WorldMapEditor__
#include <vector>

namespace Sexy
{
	class Graphics;
}
class MapEventItem;
struct MapRenderItem
{
	MapRenderItem(MapEventItem* i_mapEventItem)
	: m_mapEventItem(i_mapEventItem)
	{}
	
	MapEventItem* m_mapEventItem;
};
class ParallaxCache;
class WorldMap;
class WorldMapCamera;

class WorldMapEditor
{
public:
	virtual ~WorldMapEditor() {}
	virtual void SetDrawColor(Sexy::Graphics* i_g) = 0;
	virtual void DrawDarkBackground(Sexy::Graphics* i_g, int i_x, int i_y, int i_width, int i_height) = 0;
	virtual void DrawMapLayers(Sexy::Graphics* i_g, std::vector<MapRenderItem>& i_mapRenderList, WorldMapCamera* i_camera, ParallaxCache& i_parallaxCache) = 0;
};

#endif /* defined(__PlantsVersusZombies2_WorldMapEditor__) */
