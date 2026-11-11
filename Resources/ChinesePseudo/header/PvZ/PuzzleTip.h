/*
 * PuzzleTip.h
 *
 *  Created on: 2019-4-8
 *      Author: zhousen
 */

#ifndef PUZZLETIP_H_
#define PUZZLETIP_H_

// pop tip
class PuzzleTip : public Widget {
public:
    PuzzleTip();

    virtual void Draw(Graphics* g) override;
    virtual void Resize(const Rect& rect) override;

    virtual void SetTip(SexyString tip);

    // virtual void SetRect(Rect rect);

    virtual void SetBGImage(Image* image);
    virtual void SetFont(PrimeTypeface* font);
    void SetColor(int theIdx, const Color& theColor) override;
    virtual void SetDrawJustification(DrawStringJustification type);
    virtual void SetWrapped(bool wrapped);

protected:
    SexyString _tip;// tip description
    Rect _rect;// tip bg rect
    Image* _backgroundImg;// tip bg image
    PrimeTypeface* _font;// tip font
    Color _color;// tip color
    DrawStringJustification _drawType;// tip draw type
    bool _isWrapped;
};


#endif /* PUZZLETIP_H_ */
