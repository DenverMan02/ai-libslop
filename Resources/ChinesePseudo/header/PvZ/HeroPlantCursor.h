#ifndef HeroPlantCursor_H_
#define HeroPlantCursor_H_

#include "PVZTypes.h"
#include "BaseCursor.h"
#include "Point.h"
#include "RtObject.h"
#include "SeedPacket.h"

class HeroPlantCursor : public BaseCursor
{
public:
	RT_CLASS_DEFINE(HeroPlantCursor, BaseCursor, RtClass) {}

	HeroPlantCursor() {}
	~HeroPlantCursor();

	explicit HeroPlantCursor(const Sexy::Touch& i_boardSpaceTouch, const Sexy::Rect& i_rect, PlantTypePtr i_plantType);

	bool IsInsideOriginRect() const override;

	Point GetCursorGridPosition();
	void tryToUse();

protected:
	Sexy::SexyVector2 getCursorAnimOffset() const override;
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	void cacheOrDestroyCursor();

private:

	PlantTypePtr m_plantType;
};

#endif /* defined(__PlantsVersusZombies2__MagicBeansCursor__) */
