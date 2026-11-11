//#include "EditWidget.h"
#ifndef IMEDISPATCHER_H
#define IMEDISPATCHER_H

#include <string>
#include "Rect.h"

struct IMEKeyboardNotificationInfo
{
    Sexy::Rect  begin;
    Sexy::Rect  end;
    float       duration;
};

class IMEDelegate
{
public:
    virtual std::string getText() {return "";}
    
    virtual void setText(const std::string& text){}
    
    virtual void getFrameRect(Sexy::FRect& rect) {}
    
    virtual void deleteBackward() {}
    
    virtual void returnBackward() {}
    
    virtual void getFontInfo(std::string& fontName,float& fontSize)    {}
    
    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info)   {}
    
    virtual void keyboardDidShow(IMEKeyboardNotificationInfo& info)    {}
    
    virtual void keyboardWillHide(IMEKeyboardNotificationInfo& info)   {}
    
    virtual void keyboardDidHide(IMEKeyboardNotificationInfo& info)    {}
    
    virtual bool isNewMode() {return false;}
};

namespace Sexy {

class IMEDispatcher {

public:

	IMEDispatcher();

	~IMEDispatcher();

	void AttachIME(IMEDelegate *delegate);

	void DetachIME(IMEDelegate *delegate);

	std::string GetText();

    bool isNewMode();
    
	void SetText(std::string strText);
    
    void GetRect(Sexy::FRect& rect);
    
    void GetFontInfo(std::string& fontName,float& fontSize);
    
    void dispatchDeleteBackward();
    
    void dispatchReturnBackward();
    
    void dispatchKeyboardWillShow(IMEKeyboardNotificationInfo& info);
    
    void dispatchKeyboardDidShow(IMEKeyboardNotificationInfo& info);
    
    void dispatchKeyboardWillHide(IMEKeyboardNotificationInfo& info);
    
    void dispatchKeyboardDidHide(IMEKeyboardNotificationInfo& info);
    
	static IMEDispatcher* GetInstancePtr();

private:

	IMEDelegate *mDelegate = nullptr;

	static IMEDispatcher* pSharedIMEDispatcher;

};



}

#endif