/*
 * PVZ2UIImageButton.h
 *
 *  Created on: 2021-7-17
 *      Author: zhousen
 */

#ifndef PVZ2UIIMAGEBUTTON_H_
#define PVZ2UIIMAGEBUTTON_H_

#include "PVZ2UIButton.h"

///
/// PVZ2UIImageButton
///
class PVZ2UIImageButton : public PVZ2UIButton, public ButtonListener
{
public:
    typedef Delegate0 ClickFunc;
    PVZ2UIImageButton(int buttonID);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void SetIconImage(Image* img) { _iconImage = img; }
    void SetTitle(SexyString title) { _title = title; }
    void SetClickCallback(ClickFunc callback){ _callback = callback; }
    void UpdateParams();// should UpdateParams after set image and resize this button

protected:
    Rect _imgRect;// the rect render img
    Rect _titleRect;// the rect render title.
    Image* _iconImage;// icon image
    SexyString _title;// title str
    ClickFunc _callback;// click callback
};

#endif /* PVZ2UIIMAGEBUTTON_H_ */
