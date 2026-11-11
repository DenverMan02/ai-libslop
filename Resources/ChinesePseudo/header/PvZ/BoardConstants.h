//
//  BoardConstants.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 12/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_BoardConstants_h
#define PlantsVersusZombies2_BoardConstants_h

namespace BoardConstants
{
	bool IsCardGameScale();
	bool IsNewPVPScale();

	inline const int NUMBER_OF_ROWS()
	{
		return IsCardGameScale() ? 7 : IsNewPVPScale() ? 7 : 5;
	}

	inline const int NUMBER_OF_COLUMNS()
	{
		return IsCardGameScale() ? 13 : IsNewPVPScale() ? 13 : 9;
	}

	inline const int NUMBER_OF_SQUARES()
	{
		return NUMBER_OF_ROWS() * NUMBER_OF_COLUMNS();
	}

	inline const int GRIDSQUARE_WIDTH()
	{
		return IsCardGameScale() ? 44 : IsNewPVPScale() ? 44 : 64;
	}

	inline const int GRIDSQUARE_HEIGHT()
	{
		return IsCardGameScale() ? 54 : IsNewPVPScale() ? 54 : 76;
	}

//	const int NUMBER_OF_ROWS = GetNumberOfRows();
//	const int NUMBER_OF_COLUMNS = GetNumberOfColumns();
//	const int NUMBER_OF_SQUARES = NUMBER_OF_ROWS * NUMBER_OF_COLUMNS;
	
	constexpr int NUMBER_OF_ROWS_RAW = 5;
	constexpr int NUMBER_OF_COLUMNS_RAW = 9;

	constexpr int BOARD_WIDTH = 800;
	constexpr int BOARD_HEIGHT = 600;

	// These are in BOARD UNITS, not screen space!
	constexpr int GRID_LEFT = 200;
	constexpr int GRID_TOP = 160;
	
	constexpr int GRIDSQUARE_WIDTH_RAW = 64;
	constexpr int GRIDSQUARE_HEIGHT_RAW = 76;

    const float MYSTERIOUS_PLANTING_OFFSET_Y = -10.0f;

//	const int GRIDSQUARE_WIDTH() = GetGridSquareWidth();
//	const int GRIDSQUARE_HEIGHT() = GetGridSquareHeight();
}

#endif
