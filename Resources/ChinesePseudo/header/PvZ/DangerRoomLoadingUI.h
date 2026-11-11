/*
 * DangerRoomLoadingUI.h
 *
 *  Created on: 2015-9-17
 *      Author: jianglc
 */

#ifndef DANGERROOMLOADINGUI_H_
#define DANGERROOMLOADINGUI_H_

#include "Core.h"

class DangerRoomLoadingUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:

	DangerRoomLoadingUI();
	virtual ~DangerRoomLoadingUI();

	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

private:
    double m_Rot;
};


#endif /* DANGERROOMLOADINGUI_H_ */
