/*
 * MissileToeTargetCursor.h
 *
 *  Created on: 2017-10-19
 *      Author: Administrator
 */

#ifndef MISSILETOETARGETCURSOR_H_
#define MISSILETOETARGETCURSOR_H_

#include "BaseCursor.h"
#include "RtDb.h"
#include "Plant_MissileToe.h"

class MissileToeTargetCursor : public BaseCursor
{
public:
	RT_CLASS_DEFINE(MissileToeTargetCursor, BaseCursor, Sexy::RtClass) {}

	MissileToeTargetCursor() {}
	explicit MissileToeTargetCursor(const Sexy::Touch& i_boardSpaceTouch, PlantMissileToe* i_missileToePlant);
	virtual ~MissileToeTargetCursor();

	const PlantMissileToe* GetMissileToePlant() const { return m_missileToePlant; }

protected:
	Sexy::SexyVector2 getCursorAnimOffset() const override;
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;

private:
	void onPlantDied(Plant* i_plant);

	Sexy::SexyVector2 m_cursorOffset;
	PlantMissileToe* m_missileToePlant;
};


#endif /* MISSILETOETARGETCURSOR_H_ */
