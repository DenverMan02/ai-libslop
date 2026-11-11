//
//  DScrollView.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DScrollView_h
#define DScrollView_h

#include "DMenu.h"
#include "DTouchListener.h"
#include "DAction.h"

class DScrollView:public DTouchLayer
{
public:
    enum class Direction
    {
        NONE = -1,
        HORIZONTAL = 0,
        VERTICAL,
        BOTH
    };
    
    DScrollView& initWithViewSize(DVec2 size, DTouchLayer* container = nullptr);
    
    void setContentOffset(DVec2 offset, bool animated = false);
    DVec2 getContentOffset();
    
    void setContentOffsetInDuration(DVec2 offset, float dt);
    
    void setZoomScale(float s);
    
    void setZoomScale(float s, bool animated);
    
    float getZoomScale();
    
    
    void setZoomScaleInDuration(float s, float dt);
    
    
    DScrollView& setMinScale(float minScale) {
        _minScale = minScale;
        return *this;
    }
    
    DScrollView& setMaxScale(float maxScale) {
        _maxScale = maxScale;
        return *this;
    }
    
    DVec2 minContainerOffset();
    
    DVec2 maxContainerOffset();
    
    virtual void setTouchEnable(bool isEnable,int priority = 0) override;
    virtual bool isTouchEnable() const override;
    
    bool isDragging() const {return _dragging;}
    bool isTouchMoved() const { return _touchMoved; }
    bool isBounceable() const { return _bounceable; }
    DScrollView& setBounceable(bool bBounceable) { _bounceable = bBounceable; return *this;}
    
   
    DVec2 getViewSize() const { return _viewSize; }
    void setViewSize(DVec2 size);
    
    DTouchLayer * getContainer();
    void setContainer(DTouchLayer * pContainer);
    
    
    Direction getDirection() const { return _direction; }
    virtual DScrollView& setDirection(Direction eDirection) { _direction = eDirection; return *this;}
    
    void updateInset();
    
    
    bool isClippingToBounds() { return _clippingToBounds; }
    DScrollView& setClippingToBounds(bool bClippingToBounds) { _clippingToBounds = bClippingToBounds; return *this;}
    
    virtual void onActive() override;
    
    virtual bool onTouchBegan(const Sexy::Touch& touch) override;
    virtual void onTouchMoved(const Sexy::Touch& touch) override;
    virtual void onTouchEnded(const Sexy::Touch& touch) override;
    virtual void onTouchCancelled(const Sexy::Touch& touch) override;
    virtual void onTouchLongPress(const Sexy::Touch& touch) override;
    
    virtual void visit(const DMatrix& parentMatrix,Graphics* i_g,bool isDirty) override;
    
    virtual DScrollView& setContentSize(const DVec2 & size) override;
    virtual DVec2 getContentSize() const override;
    
    bool hasVisibleParents() const;
    
    virtual ~DScrollView();
protected:
    
    DScrollView();
    void relocateContainer(bool animated);
    void deaccelerateScrolling(float dt);
    void performedAnimatedScroll(float dt);
    void stoppedAnimatedScroll(DTransformNode* node);
    void onBeforeDraw(const DMatrix& mat,Graphics* i_g);
    void onAfterDraw(const DMatrix& mat,Graphics* i_g);
    void handleZoom();
    FRect getViewRect();
    Direction _direction;
    bool _dragging;
    DVec2 _contentOffset;
    DTouchLayer* _container;
    bool _touchMoved;
    bool _isAutoMoved;
    DVec2 _maxInset;
    DVec2 _minInset;
    bool _bounceable;
    bool _clippingToBounds;
    DVec2 _scrollDistance;
    DVec2 _touchPoint;
    float _touchLength;
    std::vector<Touch> _touches;
    DVec2 _viewSize;
    float _minScale, _maxScale;
    Rect _parentScissorRect;
    bool _scissorRestored;
    bool _containerTouchBegan;
    int  _touchPriority;
    
    DRefPtr<DSchedule> _deaccelerateScrollingAction;
    DRefPtr<DSchedule> _performedAnimatedScrollAction;
    
    DTouchListener* _touchListener;   
    
    friend class DRefPtr<DScrollView>;
};

#endif
