//
//  UIWidgetAnim.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.9.15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIWidgetAnim_h_
#define _UIWidgetAnim_h_
#include "Widget.h"
#include "PopAnimRig.h"

class UIWidgetAnim : public Sexy::Widget
{
public:
    enum
    {
        Color_Anim = 0,
    };
public:
	UIWidgetAnim();
	virtual ~UIWidgetAnim();
	virtual void			Update() override;
	virtual void			Draw(Sexy::Graphics* i_g) override;

	void					SetAnimRig(PopAnimRig* pAnim);
	void					SetAnimRig(const std::string& strName);
	PopAnimRig*				GetAnimRig() const { return m_pAnimRig; }
    
	void					SetScale(const SexyVector2& scale) { m_scale = scale; }
    const SexyVector2&      GetScale() const {return m_scale; }
   
    void                    SetCentered(bool setting) {m_bCentered = setting;}
    bool                    IsCentered() const {return m_bCentered;}
    void                    SetLabel(const std::string& i_label);
    void                    SetLabel(const std::string& i_label, std::function<void(const std::string&)> i_callBack);
    std::string             GetLabel() const;
    void                    onAnimStopped(const std::string& i_animName);
protected:
	PopAnimRig*				m_pAnimRig;
	SexyVector2				m_scale;
    bool                    m_bCentered;
    std::string             m_label;
    std::function<void(const std::string&)>    m_animStopCallBack;
};



#endif
