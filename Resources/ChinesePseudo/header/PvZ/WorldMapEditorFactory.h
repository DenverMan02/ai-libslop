//
//  WorldMapEditorFactory.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 11/26/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMapEditorFactory__
#define __PlantsVersusZombies2__WorldMapEditorFactory__

#include "Singleton.h"
#include "core.h"
#include "DefaultWorldMapEditor.h"
#include "WorldMapEditorImpl.h"

enum MapEditorFlags
{
	PVZ_BEGIN_FLAG_ENUM(EDITORFLAG_),
	
	// ENABLED
	//	- Sets the editor to enabled
	PVZ_FLAG(EDITORFLAG_ENABLED),
	
	// DRAW_BACKGROUND
	//	- Show background tiles.
	PVZ_FLAG(EDITORFLAG_DRAW_BACKGROUND),
	
	// DRAW_FOREGROUND
	//	- Show foreground tiles.
	PVZ_FLAG(EDITORFLAG_DRAW_FOREGROUND),
	
	// DRAW_HIDDEN_FOREGROUND
	//	- Show hidden foreground tiles.
	PVZ_FLAG(EDITORFLAG_DRAW_HIDDEN_FOREGROUND),
	
	// DRAW_EVENTS
	//	- Show event areas.
	PVZ_FLAG(EDITORFLAG_DRAW_EVENTS),
	
	PVZ_END_FLAG_ENUM(EDITORFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(MapEditorFlags);

class WorldMapEditorFactory : public LazySingleton<WorldMapEditorFactory>
{
public:
	WorldMapEditorFactory();
	WorldMapEditor& GetEditor();
	
	void SetEditorEnabled(bool i_isEnabled);
	bool IsEditorEnabled();
	
private:
	DefaultWorldMapEditor	mDefaultEditor;
	MapEditorFlags			mEditorFlags;
#ifdef WORLDMAP_EDITOR_ENABLED
	WorldMapEditorImpl		mWorldMapEditor;
#endif
};

#endif /* defined(__PlantsVersusZombies2__WorldMapEditorFactory__) */
