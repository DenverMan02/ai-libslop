//
//  DefaultWorldMapEditor.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 11/26/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DefaultWorldMapEditor__
#define __PlantsVersusZombies2__DefaultWorldMapEditor__

#include "WorldMapEditor.h"

class DefaultWorldMapEditor : public WorldMapEditor
{
public:
	void SetDrawColor(Sexy::Graphics* i_g);
	void DrawDarkBackground(Sexy::Graphics* i_g, int i_x, int i_y, int i_width, int i_height);
	void DrawMapLayers(Sexy::Graphics* i_g, std::vector<MapRenderItem>& i_mapRenderList, WorldMapCamera* i_camera, ParallaxCache& i_parallaxCache);
};
#endif /* defined(__PlantsVersusZombies2__DefaultWorldMapEditor__) */
