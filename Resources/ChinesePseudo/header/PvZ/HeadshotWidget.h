/*
 * HeadshotWidget.h
 *
 *  Created on: 2021-12-23
 *      Author: zhousen
 */

#ifndef HEADSHOTWIDGET_H_
#define HEADSHOTWIDGET_H_

///////////////////////////////
/// Headshot Icon Widget
///////////////////////////////
class HeadshotIconWidget : public Sexy::Widget
{
public:
	HeadshotIconWidget(int headshotID);
	virtual ~HeadshotIconWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;

	void InitView(int id);

protected:
	int _headshotID;// headshot id
	Image* _headshotBg;
	Image* _headshotFrame;
	Image* _headshotImage;// main headshot icon
};


#endif /* HEADSHOTWIDGET_H_ */
