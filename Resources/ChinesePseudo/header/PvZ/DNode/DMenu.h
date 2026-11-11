//
//  DMenu.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DMenu_h
#define DMenu_h

#include "DButton.h"
#include "DTouchListener.h"

class DTouchDelegate
{
public:
    virtual ~DTouchDelegate();
    
    virtual void setTouchEnable(bool isEnable,int priority = 0);
    virtual bool isTouchEnable()const;
    
    virtual bool onTouchBegan(const Sexy::Touch& touch) = 0;
    virtual void onTouchMoved(const Sexy::Touch& touch) = 0;
    virtual void onTouchEnded(const Sexy::Touch& touch) = 0;
    virtual void onTouchCancelled(const Sexy::Touch& touch) = 0;
    virtual void onTouchLongPress(const Sexy::Touch& touch) = 0;
    
protected:
    bool    m_bTouchEnable = false;
    int     m_touchPriority = 0;
    DTouchListener* m_pTouchListener = nullptr;
    DTransformNode* m_pNode = nullptr;
};

class DTouchLayer:public DTransformNode,public DTouchDelegate
{
public:
    virtual ~DTouchLayer() = default;
    
    virtual bool onTouchBegan(const Sexy::Touch& touch) override     {return true;}
    virtual void onTouchMoved(const Sexy::Touch& touch) override     {return ;}
    virtual void onTouchEnded(const Sexy::Touch& touch) override     {return ;}
    virtual void onTouchCancelled(const Sexy::Touch& touch) override {return ;}
    virtual void onTouchLongPress(const Sexy::Touch& touch) override {return ;}
    
    virtual void onActive() override;
protected:
    DTouchLayer();
    
    friend class DRefPtr<DTouchLayer>;
};

class DMenu : public DTouchLayer
{
public:
    enum Mode
    {
        RadioMode = 0,
        NormalMode
    };
    
    enum State
    {
        WAITING = 0,
        TOUCHING,
    };
    
    virtual ~DMenu() = default;
    
    virtual bool onTouchBegan(const Sexy::Touch& touch) override;
    virtual void onTouchMoved(const Sexy::Touch& touch) override;
    virtual void onTouchEnded(const Sexy::Touch& touch) override;
    virtual void onTouchCancelled(const Sexy::Touch& touch)override;
    virtual void onTouchLongPress(const Sexy::Touch& touch) override;
    
    virtual bool handleTouchBegan(const Sexy::Touch& touch) { return false; }
    virtual void handleTouchMoved(const Sexy::Touch& touch) {}
    virtual void handleTouchEnded(const Sexy::Touch& touch) {}
    virtual void handleTouchCancelled(const Sexy::Touch& touch) {}

    virtual DMenu& addButtons(const std::vector<DButton*> &buttons);
    virtual void setEnable(bool isEnable){m_bEnable = isEnable;}
    virtual bool isEnable()const {return m_bEnable;}
    virtual void removeChild(DTransformNode* child, bool cleanup) override;
    
    virtual void setRadioItem(DButton* item);
    
    void setMode(Mode mode){m_eMode = mode;}
    
    void align(int lineNum,float w,float h,float px,float py);
    
    Mode getMode()const {return m_eMode;}
    
    void setTargetName(const std::string& i_name) { m_targetChildName = i_name; }

protected:
    void setRadio();
    DMenu();
    virtual bool init();
    DButton* getItemForTouch(const Sexy::Touch& touch, const std::string& i_name = "");
    
protected:
    Mode             m_eMode    = NormalMode;
    bool             m_bEnable  = false;
    DButton*         m_pSelectedItem = nullptr;
    DButton*         m_pRadioItem = nullptr;
    State            m_state = WAITING;
    friend class DRefPtr<DMenu>;
    std::string m_targetChildName = "";
};

#endif
