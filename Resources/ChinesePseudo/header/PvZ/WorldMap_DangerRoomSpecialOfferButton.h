/*
 * WorldMap_DangerRoomSpecialOfferButton.h
 *
 *  Created on: 2020-1-6
 *      Author: Administrator
 */

#ifndef WORLDMAP_DANGERROOMSPECIALOFFERBUTTON_H_
#define WORLDMAP_DANGERROOMSPECIALOFFERBUTTON_H_

#include "RtObject.h"
#include "UIEasyButtonWidget.h"
#include "PVZ2UIButton.h"

class WorldMap_DangerRoomSpecialOfferButton : public PVZ2UIButton
{
public:
	WorldMap_DangerRoomSpecialOfferButton(int id, Sexy::ButtonListener* listener);

    virtual void Draw(Graphics* i_g) override;
};


#endif /* WORLDMAP_DANGERROOMSPECIALOFFERBUTTON_H_ */
