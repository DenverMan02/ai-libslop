//
//  BoardTransforms.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 8/26/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BoardTransforms__
#define __PlantsVersusZombies2__BoardTransforms__

#include "Point.h"
#include "PVZTypes.h"

namespace BoardTransforms
{
	// Grid to BoardSpace - Bounded
	Sexy::Point GridToBoardSpace(const Sexy::Point& i_gridPoint);
	int GridToBoardSpaceX(const int i_gridX);
	int GridToBoardSpaceY(const int i_gridY);
	Sexy::Point GridToBoardSpacePos(int i_gridX, int i_gridY);
	
	// Grid to BoardSpace - Unbounded
	Sexy::Point GridToBoardSpaceUnbounded(const Sexy::Point &i_gridPoint);
	int GridToBoardSpaceXUnbounded(const int i_gridX);
	int GridToBoardSpaceYUnbounded(const int i_gridY);
	float GridToBoardSpaceXUnbounded_Float(const float i_gridX);

	// Grid to BoardSpace Rect - Unbounded
	Sexy::Rect GridToBoardSpaceRect(const int i_gridX, const int i_gridY, const int i_gridExtentsX = 1, const int i_gridExtentsY = 1);
	Sexy::Rect GridToBoardSpaceRect(const Sexy::Point& i_gridPoint);
	Sexy::Rect GridToBoardSpaceRect(const Sexy::Point& i_gridPoint, const Sexy::Point& i_gridExtents);
	Sexy::Rect GridRectToBoardSpaceRect(const Sexy::Rect& i_gridRect);
	
	// BoardSpace to Grid - Bounded
	void BoardSpaceToGrid(const int i_x, const int i_y, int& o_col, int& o_row);
	void BoardSpaceToGrid(const float i_x, const float i_y, int& o_col, int& o_row);
	Sexy::Point BoardSpaceToGrid(const int i_x, const int i_y);
	Sexy::Point BoardSpaceToGrid(const float i_x, const float i_y);
	int BoardSpaceToGridX(const int i_pixelX);
	int BoardSpaceToGridX(const float i_pixelX);
	int BoardSpaceToGridY(const int i_pixelY);
	int BoardSpaceToGridY(const float i_pixelY);
	
	// BoardSpace to Grid - Keep on Board
	int BoardSpaceToGridXKeepOnBoard(const int i_pixelX);
	int BoardSpaceToGridXKeepOnBoard(const float i_pixelX);
	int BoardSpaceToGridYKeepOnBoard(const int i_pixelY);
	int BoardSpaceToGridYKeepOnBoard(const float i_pixelY);
	
	// Planting BoardSpace to Grid
	int PlantingBoardSpaceToGridX(const int i_pixelX, PlantTypePtr i_seedType);
	int PlantingBoardSpaceToGridX(const float i_pixelX, PlantTypePtr i_seedType);
	int PlantingBoardSpaceToGridY(const int i_pixelY, PlantTypePtr i_seedType);
	int PlantingBoardSpaceToGridY(const float i_pixelY, PlantTypePtr i_seedType);
	void OffsetYForPlanting(int &i_y, PlantTypePtr i_seedType);
	
	// BoardSpace to Grid - Unbounded
	int BoardSpaceToGridXUnbounded(const int i_pixelX);
	int BoardSpaceToGridXUnbounded(const float i_pixelX);
	float BoardSpaceToGridXUnboundedFloat(const float i_pixelX);
	int BoardSpaceToGridYUnbounded(const int i_pixelY);
	int BoardSpaceToGridYUnbounded(const float i_pixelY);
	float BoardSpaceToGridYUnboundedFloat(const float i_pixelY);
    Sexy::Point BoardSpaceToGridUnbounded(const SexyVector3& i_boardPosition);
	
	// Utilities
	void ClampGridCoords(int& io_gridX, int& io_gridY);
    bool IsGridCoordinateOnBoard(const int i_gridX, const int i_gridY);
}

#endif /* defined(__PlantsVersusZombies2__BoardTransforms__) */
