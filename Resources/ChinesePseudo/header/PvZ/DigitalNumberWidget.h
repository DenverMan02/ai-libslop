/*
 * DigitalNumberWidget.h
 *
 *  Created on: 2021-8-23
 *      Author: zhousen
 */

#ifndef DIGITALNUMBERWIDGET_H_
#define DIGITALNUMBERWIDGET_H_

#include "RtObject.h"
#include "RtSerial.h"
#include "ReflectionBuilder.h"

class DigitalNumberWidget : public Sexy::Widget
{
public:
	RT_CLASS_DEFINE(DigitalNumberWidget, Sexy::Widget, RtClass);

	DigitalNumberWidget();
	virtual ~DigitalNumberWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void Resize(int x, int y, int width, int height) override;

	void SetNumberCount(int count);
	void SetNumber(int number);
	void InitNumberImages(std::vector<ImagePtr> images);

protected:
	void UpdateNumber();

protected:
	int _digitalNumCount;// the count of number
	int _digitalNumber;// real number
	std::vector<int> _digitalNumberList;// put single number in list
	std::vector<ImagePtr> _digitalNumberImages;// number images, according to 0 ~ 9
	int _itemWidth;// digital number width
	int _itemHeight;// digital number height
};


#endif /* DIGITALNUMBERWIDGET_H_ */
