//
//  DangerRoomDialog.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomDialogContents__
#define __PlantsVersusZombies2__DangerRoomDialogContents__

#include "Precompile.h"

class DangerRoomDialogContents : public Sexy::Widget
{
public:
	DangerRoomDialogContents(class PVZ2UIDialog* i_parent, class DangerRoomStatScreen* i_dangerRoomScreen);
	virtual ~DangerRoomDialogContents();
	
	virtual void		Update();
	virtual void		Draw(Graphics* i_g);
	
	void				SetFirstLine(SexyString i_lineName, SexyString i_lineInfo, const std::vector<bool>& i_mowersLeft, const int i_levelReached);
	void				SetSecondLine(SexyString i_lineName, SexyString i_lineInfo, const int i_highestLevelReached, const bool i_newHighestRecord);
	void				SetPlantfoodCount(const int i_plantfoodCount);
	void				FinalizeContentSize();
	
private:
	
	void				drawFirstLine(Sexy::Graphics* i_g, const int i_leftStartX, const int i_leftStartY, const int i_leftLineWidth, const int i_rightStartX, const int i_rightStartY, const int i_rightLineWidth, const int i_lineHeight);
	
	// First line
	std::vector<bool>	m_mowersLeft;
	int					m_levelReached;
	SexyString			m_firstLineName;
	SexyString			m_firstLineInfo;
	
	
	// Second line
	int					m_highestLevelReached;
	bool				m_newHighestRecord;
	SexyString			m_secondLineName;
	SexyString			m_secondLineInfo;

	// Third line
	int					m_plantfoodCount;
	SexyString			m_forthLineName;
	SexyString			m_forthLineInfo;
	int					m_plantfoodIconX;
	
	class PVZ2UIDialog*				m_parent;
	class DangerRoomStatScreen*		m_dangerRoomScreen;
};

#endif /* defined(__PlantsVersusZombies2__DangerRoomDialog__) */
