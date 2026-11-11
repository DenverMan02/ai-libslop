//
//  DButton.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DButton_h
#define DButton_h

#include "DNode.h"

class DButton:public DTransformNode
{
    typedef DTransformNode Super;
public:
    virtual bool isEnabled()const ;
    virtual void setEnabled(bool ok);
    
    virtual bool isEnabledTouch()const ;
    virtual void setEnabledTouch(bool ok);

    virtual DButton& setCallback(const std::function<void(DRef*)>& cb);
    virtual DButton& setCallbackWithTouch(const std::function<void(DRef*, const Sexy::Touch&)>& cb);
    virtual DButton& setSelectCallback(const std::function<void(DRef*)>& cb);
    virtual DButton& setSelectCallbackWithTouch(const std::function<void(DRef*, const Sexy::Touch&)>& cb);
    virtual DButton& setSelectMoveCallbackWithTouch(const std::function<void(DRef*, const Sexy::Touch&)>& cb);
    virtual DButton& setLongPressCallbackWithTouch(const std::function<void(DRef*, const Sexy::Touch&)>& cb);
    virtual DButton& setUnSelectCallback(const std::function<void(DRef*)>& cb);
    virtual DButton& setNormalNode(DTransformNode* node);
    virtual DButton& setSelectNode(DTransformNode* node);
    virtual DButton& setTouchMoveNode(DTransformNode* node);
    virtual DButton& setDisableNode(DTransformNode* node);
    
    virtual DButton& setBounce(bool isBounce);
    virtual bool     isBounce()const {return m_bBounce;}
    
    virtual DButton& setTouchMode(bool i_touch);
    virtual bool     isTouchMode()const {return m_bTouch;}

    virtual void removeAllChildren(bool cleanup = true) override;
    
    virtual FRect getRect();
    
    virtual void selected();
    virtual void unselected();
    virtual bool isSelected()const;
    virtual void active();
    virtual void active(const Sexy::Touch& touch);
    
    virtual void selected(const Sexy::Touch& touch);
    virtual void selectedMove(const Sexy::Touch& touch);
    virtual void longPress(const Sexy::Touch& touch);

protected:
    DButton();
    virtual ~DButton() = default;
    
    void updateVisibility();
    
    bool            m_bBounce = false;
    bool            m_bSelected = false;
    bool            m_bEnabled = true;
    bool			m_bEnabledTouch = true;
    float           m_originalScale = 1.0f;
    bool			m_bTouch = false;
    // callback
    std::function<void(DRef*)> m_callback = nullptr;
    std::function<void(DRef*, const Sexy::Touch&)> m_callbackWithTouch = nullptr;
    std::function<void(DRef*)> m_selectCallback = nullptr;
    std::function<void(DRef*)> m_unselectCallback = nullptr;
    std::function<void(DRef*, const Sexy::Touch&)> m_selectCallbackWithTouch = nullptr;
    std::function<void(DRef*, const Sexy::Touch&)> m_selectMoveCallbackWithTouch = nullptr;
    std::function<void(DRef*, const Sexy::Touch&)> m_longPressCallbackWithTouch = nullptr;
    
    DTransformNode* m_pNormalNode = nullptr;
    DTransformNode* m_pSelectNode = nullptr;
    DTransformNode* m_pDisableNode = nullptr;
    DTransformNode* m_pTouchMoveNode = nullptr;
    
    DVec2 m_touchPoint;

    friend class DRefPtr<DButton>;
};

class DButtonGroup:public DButton
{
    typedef DButton Super;
public:
    virtual void active() override;
    virtual void active(const Sexy::Touch& touch) override;
    virtual void selected() override;
    virtual void selected(const Sexy::Touch& touch) override;
    virtual void unselected() override;
    virtual void setEnabled(bool ok) override;
    
    DButtonGroup& addSubItem(DButton *item);
    
    DButton* getSelectedItem();
    
    inline unsigned int getSelectedIndex() const { return m_selectedIndex; };
    
    void setSelectedIndex(unsigned int index);
   
    inline const DArray<DButton*>& getSubItems() const { return m_subItems; };
    
    inline DArray<DButton*>& getSubItems() { return m_subItems; };
    
    inline void setSubItems(const DArray<DButton*>& items) { m_subItems = items;}
    
protected:
    DButtonGroup();
    virtual ~DButtonGroup();
protected:
    unsigned int m_selectedIndex;
    DButton*     m_selectedItem = nullptr;
    
    DArray<DButton*> m_subItems;
    
    friend class DRefPtr<DButtonGroup>;
};

#endif
