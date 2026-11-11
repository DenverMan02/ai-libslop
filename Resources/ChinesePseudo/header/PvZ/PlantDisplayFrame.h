/*
 * PlantDisplayFrame.h
 *
 *  Created on: 2019-5-7
 *      Author: Administrator
 */

#ifndef PLANTDISPLAYFRAME_H_
#define PLANTDISPLAYFRAME_H_

#include "Widget.h"

class PlantDisplayFrame : public Sexy::Widget, Sexy::ButtonListener
{
public:
	PlantDisplayFrame(const std::string& i_plantName, const Sexy::Rect& i_rect, const std::string& i_imageName);
	~PlantDisplayFrame();

	virtual void	Draw(Sexy::Graphics* i_g) override;
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g) override;

	void InitView();
	virtual void	ButtonPress(int i_id) override;
	virtual void	ButtonDepress(int i_id) override;

	void SetVisible(bool isVisible) override;
	class PlantDisplayBoard* GetPlantDisplayPtr();

private:
	class PlantDisplayBoard* m_plantDisplay;
	std::string m_plantName;
	Sexy::Rect m_drawRect;
	Sexy::RtWeakPtr<Sexy::Image> m_backgroundImage;
};


#endif /* PLANTDISPLAYFRAME_H_ */
