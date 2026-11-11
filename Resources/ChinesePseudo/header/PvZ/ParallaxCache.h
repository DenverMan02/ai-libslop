//
//  ParallaxCache.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 11/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ParallaxCache__
#define __PlantsVersusZombies2__ParallaxCache__

#include <vector>

class WorldMapPropertySheet;

/**
 * A simple data structure that can load up multipliers and offsets
 * for different parallax layers, and make them easy to look up
 * by by int8 parallax layer ID.
 *
 * Layers as of 11/1/13:
 * -4 to -1 : Foreground
 * 0        : Interaction layer / no parallax
 * 1 to 9   : Background
 * 10       : Skybox / infinite parallax
 *
 */
class ParallaxCache
{
public:
	ParallaxCache();
	virtual ~ParallaxCache() {};
	
	void	InitializeMultipliers(WorldMapPropertySheet& i_worldMapPropertySheet);
	void	RecalculateOffsets(float i_cameraOffset);
	
	float	GetOffsetForLayer(int i_layerIndex);
	
	int		GetMinimumLayerIndex();
	int		GetMaximumLayerIndex();
	
protected:
	void	setMultiplier(int i_layerIndex, float i_speedMultiplier);
	float	getMultiplier(int i_layerIndex);
	
private:
	
	/**
	 * Internally, we use an offset to flatten foreground (negative) and background
	 * (positive) layer indices into a single vector.
	 */
	int		layerIndexToInternalIndex(int i_layerIndex);
	void	expandStorageIfNeededForLayer(int i_layerIndex);
	
	int						m_numberOfForegroundLayers;
	std::vector<float>		m_multipliers;
	std::vector<float>		m_offsets;
};

#endif /* defined(__PlantsVersusZombies2__ParallaxCache__) */
