//
//  DTextField.h
//  DCore
//
//  Created by lzjseed on 16/8/22.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DTextField_h
#define DTextField_h

#include "DStringNode.h"
#include "SexyAppFramework/IMEDispatcher.h"
#include "DMenu.h"

enum class DTextFieldType
{
    Type_Default,
    Type_PhoneNum,
    Type_Email,
};

class DTextField:public DStringNode,public IMEDelegate,public DTouchDelegate
{
    typedef DStringNode Super;
protected:
    DTextField();
    virtual ~DTextField();
public:
    void attachIME();
    void detachIME();

    virtual void cleanup() override;
    
    virtual void deleteBackward() override;
    
    virtual std::string getText() override;
    
    virtual void setText(const std::string& text) override;
    
    virtual DTextField& setTextFieldType(DTextFieldType type) {m_textFieldType = type; return *this;}
    
    virtual DTextFieldType getTextFieldType()const {return m_textFieldType;}
    
    virtual void getFrameRect(Sexy::FRect& rect) override;
    
    virtual void getFontInfo(std::string& fontName,float& fontSize) override;
    
    virtual bool isNewMode() override {return true;}
    
    virtual void draw(const DMatrix &mat, Sexy::Graphics *i_g) override;
    
    virtual DTextField& setPlaceHolderText(const std::string& text,bool isFromFile = false);
    
    virtual const std::string getPlaceHolderText()const;
    
    virtual const Color& getPlaceHolderColor() const {return m_placeHolderColor;}
    
    virtual DTextField& setPlaceHolderColor(const Color& color) {m_placeHolderColor = color; return *this;}
    
    virtual const Color& getInputColor() const {return m_inputColor;}
    
    virtual DTextField& setInputColor(const Color& color) {m_inputColor = color; return *this;}
    
    virtual DTextField& setCharNum(size_t num);
    
    virtual size_t getCharNum()const;
    
    virtual void  keyboardWillShow(IMEKeyboardNotificationInfo& info) override{}
    
    virtual void  keyboardDidShow(IMEKeyboardNotificationInfo& info)  override{}
    
    virtual void  keyboardWillHide(IMEKeyboardNotificationInfo& info) override{}
    
    virtual void keyboardDidHide(IMEKeyboardNotificationInfo& info) override;
    
    virtual void  returnBackward() override;
    
    virtual FRect getRect();
    
    virtual bool  onTouchBegan(const Sexy::Touch& touch) override;
    virtual void  onTouchMoved(const Sexy::Touch& touch) override;
    virtual void  onTouchEnded(const Sexy::Touch& touch) override;
    virtual void  onTouchCancelled(const Sexy::Touch& touch) override;
    virtual void  onTouchLongPress(const Sexy::Touch& touch) override;
    
    virtual void  onActive()override;
    
    virtual DTextField& setEditFinish(const std::function<void()>& cb) {m_editFinishCb = cb;return *this;}
    
protected:
    
    std::function<void()> m_editFinishCb = nullptr;
    
    DTextFieldType m_textFieldType = DTextFieldType::Type_Default;
    Color    m_placeHolderColor;
    Color    m_inputColor;
    DString  m_placeHolder;
    bool     m_placeHolderWithFile = false;
    DString  m_inputText;
    size_t   m_charNum = 8;
    size_t   m_charPos = 0;
    float    m_posX = 0;
    float    m_posY = 0;
    float    m_cursorHeight = 0;
    unsigned int m_countDownTime = 0;
    bool     m_bDisplayCursor = false;
    bool     m_bShowCursor = false;
protected:
    friend class DRefPtr<DTextField>;
};

#endif
