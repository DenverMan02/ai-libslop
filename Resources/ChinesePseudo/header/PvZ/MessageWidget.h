#ifndef __MESSAGEWIDGET_H__
#define __MESSAGEWIDGET_H__
// Message Widget
//
// Display a message across the board for a set duration. 
//

#include "TimeMgr.h"
#include "MessageWidgetEnums.h"
#include "Renderable.h"
#include "PrimeTextWidget.h"

class LawnApp;
class Renderable;
class PopAnimRig;

struct LetterPopAnimTracker
{
	LetterPopAnimTracker() : m_popAnimRig(NULL) {}
	PopAnimRig* m_popAnimRig;

	void onAnimStopped(const std::string &i_animName);
};

//
// A timed message displayed on the board. 
//
class MessageWidget : public Renderable
{

public:
    MessageWidget();
	~MessageWidget();
    
    // Sets the text and implicitly the duration of the message. 
	void			SetLabel(const SexyString &i_newLabel, MessageStyle i_messageStyle);
	void			SetLabel(const SexyString &i_newLabel, MessageStyle i_messageStyle, float duration);
	void			Update();
    void			Draw(Sexy::Graphics* g);
    
    void			Clear();
  
	bool			IsBeingDisplayed();
	pvztime_t		GetDuration();
	RenderLayer		GetRenderLayer();
    

    
private:
    void			clearPAMs();
	void			clearLabel();
    
    //PVZ2_CHINESE_BEGIN
    PrimeTypeface*	getFont();
    //Font*	getFont();
    //PVZ2_CHINESE_BEGIN
	void			layoutReanimText();
    
    static const int MAX_MESSAGE_LENGTH = 128;
    
	SexyChar        m_label[MAX_MESSAGE_LENGTH];
	pvztime_t       m_displayTime;
	pvztime_t       m_duration;
	MessageStyle    m_messageStyle;
    
	LetterPopAnimTracker m_textPAR[MAX_MESSAGE_LENGTH];
    
    PrimeTextWidget*    m_textWidget;
};

inline void MessageWidget::Clear()
{
    clearLabel();
}

inline pvztime_t MessageWidget::GetDuration()
{
    return m_duration;
}

#endif //__MESSAGEWIDGET_H__
