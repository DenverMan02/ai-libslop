/*
 * PlantPot.h
 *
 *  Created on: Jan 12, 2015
 *      Author: lijie
 */

#ifndef PLANTPOT_H_
#define PLANTPOT_H_

#include "GridItem.h"

typedef RtWeakPtr<class PlantPot> PlantPotPtr;

class PlantPot : public GridItem
{
public:
	RT_CLASS_DEFINE(PlantPot, GridItem, RtClass);

	PlantPot();
	virtual ~PlantPot();

	void Init(ImagePtr potImage, float offsetY);

protected:
	virtual int CalcRenderOrder() const override;
	virtual void onDraw(class Sexy::Graphics* i_g) override;

protected:
	ImagePtr m_potImage;
	float m_offsetY;
};


#endif /* PLANTPOT_H_ */
