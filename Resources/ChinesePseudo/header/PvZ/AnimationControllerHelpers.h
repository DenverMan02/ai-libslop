//
//  AnimationControllerHelpers.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 6/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_AnimationControllerHelpers_h
#define PlantsVersusZombies2_AnimationControllerHelpers_h

#include "AnimationMgr.h"
#include "TimeMgr.h"
#include "MessageWidget.h"
#include "WorldMap.h"
#include "PopAnimRig.h"
#include "ResourceHelpers.h"

//
// Send an AudioEvent to audiomgr.
//
class AnimMgrSendAudioEvent : public AnimationController
{
public:
    RT_CLASS_DEFINE(AnimMgrSendAudioEvent, AnimationController, RtClass);
    
    static AnimMgrSendAudioEvent* Create(const std::string& i_eventName)
    {
        return GameObject::Create<AnimMgrSendAudioEvent>(PVZDB::TABLE_GAMEOBJECTS)->Init(i_eventName);
    }
    
    AnimMgrSendAudioEvent* Init(const std::string& i_eventName)
    {
        SuperClass::Init(0);
        m_eventName = i_eventName;
        SetDescription("AnimMgrSendAudioEvent: " + i_eventName);
        
        return this;
    }
    
    
    void Update(pvztime_t i_time) override;
    
private:
    AnimMgrSendAudioEvent() {} // don't new up one of these 
    
    std::string m_eventName;
};



//
// Play a PAM for the animation manager, call a delegate when the animation is done. 
//
class PlayPAM: public AnimationController
{
public:
    enum PlayPAM_State
    {
        INITIAL,
        PLAYING,
        DONE,
    };
    

    RT_CLASS_DEFINE(PlayPAM, AnimationController, RtClass);
    
    static PlayPAM* Create()
    {
        return GameObject::Create<PlayPAM>(PVZDB::TABLE_GAMEOBJECTS);
    }

	static PlayPAM* Create(Point i_pos, const std::string& i_popanimName, RtWeakPtr<RtObject> i_callee, const std::string& i_method)
	{
		return Create()->Init(i_pos, i_popanimName, {i_callee, i_method});
	}

	static PlayPAM* Create(Point i_pos, const std::string& i_popanimName)
	{
		return Create()->Init(i_pos, i_popanimName, {});
	}

	//
	// PlayPAM(Pos, ANIM_NAME, OptionalDelegate)
	//
	PlayPAM* Init(Point i_pos, const std::string& i_popanimName, PopAnimRig::AnimStoppedReflectionDelegate i_animStoppedDelegate = {})
	{
		SuperClass::Init(PVZ_EOT());
		m_pos = i_pos;
		m_state = INITIAL;
		m_animStoppedDelegate = i_animStoppedDelegate;
		PopAnimRig* popAnimRig = PopAnimRig::CreateRig(GetPAMByName(i_popanimName).Get());
		SexyTransform2D trans;
		trans.Translate(S(m_pos.mX), S(m_pos.mY));
		popAnimRig->SetRenderTransform(trans);
		m_popAnimRig = popAnimRig->GetPtr();
		SetDescription("PlayPAM: " + i_popanimName);
		SetDuration(PVZ_EOT()/2.0f);
		return this;
	}

	bool AnimIsDone(pvztime_t i_time) // override should remove call
	{
		return DONE == m_state;
	}

	void Update(pvztime_t i_time) override
	{
		if (INITIAL == m_state)
		{
			m_popAnimRig->PlayAndStop("animation", SELECT_EXACT, {GetPtr(), "onAnimDone"});
			m_state = PLAYING;
		}
		else if (PLAYING == m_state)
		{
			m_popAnimRig->UpdateAnim(i_time, PVZ_Dt());
		}
	}

	void AddToRenderQueue(class RenderQueue* i_queue) override;


private:
	void onDestroy() override
	{
		SuperClass::onDestroy();
		SAFE_DELETE_GAMEOBJ(m_popAnimRig);
	}

	void onAnimDone(const std::string& i_animLabel)
	{
		if (PLAYING == m_state)
		{
			m_state = DONE;               // tell cutscene mgr we're done.
			m_popAnimRig->Destroy();

			if (m_animStoppedDelegate)
			{
				m_animStoppedDelegate.GetDelegate()("animation");
			}
		}
	}

	void drawPAM(class Graphics* i_g);


    PlayPAM_State  m_state = INITIAL;
    PopAnimRig::AnimStoppedReflectionDelegate m_animStoppedDelegate;
    Point       m_pos;
    PopAnimRigPtr m_popAnimRig;
};


//
// Roll lawnmowers into scene.
//
class AnimateLawnMowers : public AnimationController 
{
    public:
    RT_CLASS_DEFINE(AnimateLawnMowers, AnimationController, RtClass);
    
    
    static AnimateLawnMowers* Create()
    {
        return GameObject::Create<AnimateLawnMowers>(PVZDB::TABLE_GAMEOBJECTS);
    }
    
    static AnimateLawnMowers* Create(pvztime_t i_duration, pvztime_t i_lawnMowerAnimTime)
    {
        return Create()->Init(i_duration, i_lawnMowerAnimTime);
    }
    
    //
    // AnimateLawnMowers(duration, lawnMowerAnimationTime)
    //
    AnimateLawnMowers* Init(pvztime_t i_duration, pvztime_t i_lawnMowerAnimTime)
    {
        SuperClass::Init(i_duration);
        m_lawnMowerAnimTime = i_lawnMowerAnimTime;
        
        return this; // for fluency.
    }

    
    void Update(pvztime_t i_time) override;
    
private:
    pvztime_t   m_lawnMowerAnimTime = 0;
    
};

//
// Roll bombs into scene.
//
class AnimateBombs : public AnimationController
{
    public:
    RT_CLASS_DEFINE(AnimateBombs, AnimationController, RtClass);

    static AnimateBombs* Create(pvztime_t i_duration)
    {
    	AnimateBombs* animateBombs = GameObject::Create<AnimateBombs>(PVZDB::TABLE_GAMEOBJECTS);
    	animateBombs->Init(i_duration);
        return animateBombs;
    }

    virtual void Update(pvztime_t i_time) override;
};

//
// Draw a message ...
// 
class DrawMessage: public AnimationController, public Renderable
{
    RT_CLASS_DEFINE(DrawMessage, AnimationController, RtClass);

    DrawMessage();

    static DrawMessage* Create()
    {
        return GameObject::Create<DrawMessage>(PVZDB::TABLE_GAMEOBJECTS);
    }

    static DrawMessage* Create(const std::string& i_advice)
    {
    	DrawMessage* advice = DrawMessage::Create();
        advice->SetDesc(i_advice);

        return advice;
    }

    static DrawMessage* Create(const SexyString& i_advice)
    {
    	DrawMessage* advice = DrawMessage::Create();
        advice->SetDesc(i_advice);

        return advice;
    }

    void SetDesc(const SexyString& desc);
    void SetDesc(const std::string& desc);
    void SetRect(const Rect& rect);
    void SetColor(const Color& color);
    void SetFont(PrimeTypeface* font);

	void AddToRenderQueue(class RenderQueue* i_queue) override;
	void Draw(Graphics* i_graphics) override;

protected:
	SexyString m_desc;
	Rect m_rect;
	Color m_color;
	PrimeTypeface* m_font;
};

//
// Show a message Widget...
//
class ShowAdvice: public AnimationController, public Renderable
{
    RT_CLASS_DEFINE(ShowAdvice, AnimationController, RtClass);
    
    //
    // ShowAdvice()
    //
    ShowAdvice():m_offset(0,0)
    {
        SetDescription("ShowAdvice");
    }
    
    static ShowAdvice* Create()
    {
        return GameObject::Create<ShowAdvice>(PVZDB::TABLE_GAMEOBJECTS);
    }
    
    static ShowAdvice* Create(const SexyString& i_advice, MessageStyle i_messageStyle)
    {
        ShowAdvice* advice = ShowAdvice::Create();
        advice->SetLabel(i_advice, i_messageStyle);
        
        return advice;
    }
    
    // 
    // SetLabel(advice, messageStyle) 
    //
    void SetLabel(const SexyString& i_advice, MessageStyle i_messageStyle);
    
    void SetLabel(const SexyString& i_advice, MessageStyle i_messageStyle, float duration);
    
    ShowAdvice* Init(const SexyString& i_advice, MessageStyle i_messageStyle)
    {
        SetLabel(i_advice, i_messageStyle);
        return this;
    }
    
    void SetOffset(const Point& i_offset)
    {
        m_offset = i_offset;
    }
    
    void Update(pvztime_t i_time) override   {}
    
	void AddToRenderQueue(class RenderQueue* i_queue) override;

	void Draw(Graphics* i_graphics) override;
	void InnerDraw(Graphics* i_g) override;

private:
	void onPostLoad() override
	{
		SuperClass::onPostLoad();

		Init(m_advice, m_messageStyle);
	}

	SexyString      m_advice;
	MessageStyle    m_messageStyle = MESSAGE_STYLE_OFF;
	Point			m_offset;
	MessageWidget	m_messageWidget;
};

typedef RtWeakPtr<RtObject> ShowAdviceWkPtr;

class WorldMapCamera;

//
// A bouncing arrow. 
//
class BouncingArrow: public AnimationController , public Renderable
{
public:
    RT_CLASS_DEFINE(BouncingArrow, AnimationController, RtClass);
    
    static BouncingArrow* Create()
    {
        return GameObject::Create<BouncingArrow>(PVZDB::TABLE_GAMEOBJECTS);
    }
    
    static BouncingArrow* Create(Point i_pos, int i_dur, int i_renderOrder)
    {
        return Create()->Init(i_pos, i_dur, i_renderOrder);
    }
    
    BouncingArrow* Init(Point i_pos, int i_dur, int i_renderOrder)
    {
        SuperClass::Init(PVZ_EOT());
		m_Pos = i_pos;
		m_RenderOrder = i_renderOrder;
        m_Rot = 0;
        m_OffsetY = 0;
        m_arrowRig.ClearId();
        return this;
    }
    
    BouncingArrow()
    {
		m_Pos = Point(0,0);
		m_RenderOrder = 0;
        m_Rot = 0;
        m_OffsetY = 0;
        m_arrowRig.ClearId();
    }
    
    
    void				AddToRenderQueue(class RenderQueue* i_queue) override;
    void				Update(pvztime_t i_time) override;
    void				Draw(Graphics* i_graphics) override;
    void				DrawWithCamera(Graphics* i_graphics, WorldMapCamera* i_camera);
	
	inline void			    SetArrowAnimRig(PopAnimRigPtr i_animRig);
	inline PopAnimRigPtr	GetArrowAnimRig();
    
    Point				m_Pos;
    int					m_OffsetY;
    int					m_Rot;
    int					m_RenderOrder;
	
private:

    void onDestroy() override
    {
        SuperClass::onDestroy();
        SAFE_DELETE_GAMEOBJ(m_arrowRig);
    }
    
	PopAnimRigPtr		m_arrowRig;
};

typedef RtWeakPtr<BouncingArrow> BouncingArrowWkPtr;

inline void BouncingArrow::SetArrowAnimRig(PopAnimRigPtr i_animRig)
{
	m_arrowRig = i_animRig;
}

inline PopAnimRigPtr BouncingArrow::GetArrowAnimRig()
{
	return m_arrowRig;
}

#endif
