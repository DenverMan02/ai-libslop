//
//  WorldMapEditorImpl.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 11/25/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMapEditorImpl__
#define __PlantsVersusZombies2__WorldMapEditorImpl__
#include "WorldMapEditor.h"

#ifndef RELEASEFINAL
// Comment this line to compile and run a little bit faster ...
// and disable the editor, of course.
#define WORLDMAP_EDITOR_ENABLED
#endif

#ifdef WORLDMAP_EDITOR_ENABLED
enum MapEditorMode
{
	EDITORMODE_ISLAND,
	EDITORMODE_DOODADS,
	EDITORMODE_EVENTS,
	EDITORMODE_SELECT,
};

class WorldMapEditorImpl : public WorldMapEditor
{
public:
	WorldMapEditorImpl();

	void SetDrawColor(Sexy::Graphics* i_g);
	void DrawDarkBackground(Sexy::Graphics* i_g, int i_x, int i_y, int i_width, int i_height);
	void DrawMapLayers(Sexy::Graphics* i_g, std::vector<MapRenderItem>& i_mapRenderList, WorldMapCamera* i_camera, ParallaxCache& i_parallaxCache);

	// Non-interface
	void SetEditorMode(const MapEditorMode i_mode);
	const MapEditorMode GetEditorMode();
	
//private:
	MapEditorMode m_editorMode;

	bool m_editorHideOtherLayers;
	bool m_editorHideOtherParallaxLayers;
	int m_editorCurrentEditParallaxLayer;
	int m_editorCurrentEditLayer;
};
#endif

#endif /* defined(__PlantsVersusZombies2__WorldMapEditorImpl__) */
