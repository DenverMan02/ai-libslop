
#ifndef __SCROLLWIDGET_H__
#define __SCROLLWIDGET_H__

#include "ProxyWidget.h"

namespace Sexy
{
	class ScrollWidget;
	class PageControl;
    
    class ScrollSnapper
    {
    public:
        virtual ~ScrollSnapper() {}
        virtual void DoSnap(ScrollWidget* i_scrollWidget) = 0;
        virtual void SelectSnapTarget(ScrollWidget *i_scrollWidget) = 0;
    };
    
    class DefaultScrollSnapper : public ScrollSnapper
    {
    public:
        static ScrollSnapper& GetInstance();
        virtual void DoSnap(ScrollWidget* i_scrollWidget){}
        virtual void SelectSnapTarget(ScrollWidget *i_scrollWidget){}
    };
	class ScrollWidgetListener
	{
	public:
        virtual ~ScrollWidgetListener() {}
        virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) = 0;
        virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) = 0;
        virtual void ScrollTouchMotion( const Sexy::Touch& touch ) {}
        virtual void ScrollTouchEnd( const Sexy::Touch& touch ) {}
        virtual void ScrollerMoved(Sexy::ScrollWidget* i_scrollWidget) {}
	};
	
	class ScrollWidget : public Widget, public ProxyWidgetListener
	{
		RT_CLASS_DEFINE(ScrollWidget, Widget, RtClass);
		typedef Widget super;
	public:
		
		enum ScrollMode
		{
			SCROLL_DISABLED = 0,
			SCROLL_HORIZONTAL = 1,
			SCROLL_VERTICAL = 2,
			SCROLL_BOTH = 3,
		};
		
		enum Alignment
		{
			ALIGN_MAN,
			ALIGN_MIN,
			ALIGN_MID,
			ALIGN_MAX,
		};
		
		enum Colors
		{
			COLOR_BACKGROUND,
		};
		
		ScrollWidget( ScrollWidgetListener* listener );
		ScrollWidget();
		~ScrollWidget();

        void SetScrollSnapper(ScrollSnapper* scrollSnapper);
		void SetPageControl( PageControl* pageControl );
		void SetAlignment( Alignment alignX, Alignment alignY );
		void SetScrollMode( ScrollMode mode );
		void SetScrollInsets( const Insets& insets );
		void SetScrollOffset( FPoint anOffset, bool animated );
		void ScrollToMin( bool animated );
		void ScrollToPoint( const Point& point, bool animated );
		void ScrollRectIntoView( const Rect& rect, bool animated );
		void EnableBounce( bool enable );
		void EnablePaging( bool enable );
		void EnableIndicators( Image* indicatorsImage, Image* indicatorsBackgroundImage = NULL);
		void SetIndicatorsInsets( const Insets& insets );
		void FlashIndicators();
		void SetPageHorizontal( int page, bool animated );
		void SetPageVertical( int page, bool animated );
		void SetPage( int hpage, int vpage, bool animated );
		int GetPageHorizontal();
		int GetPageVertical();
		void SetBackgroundImage( Image* image );
		void SetPermanentIndicators(bool permanent);
		void EnableBackgroundFill( bool enable );
		void AddOverlayImage( Image* image, const Point& offset );
		void EnableOverlays( bool enable );
		
		FPoint GetScrollOffset() const;
		
		void SetTimeDTForScrolling( const float dt );

		bool GetNeedsScroller() const;
		FPoint GetScrollMin() const;
		FPoint GetScrollMax() const;
		
		void AddWidget( Widget* theWidget );
		void RemoveWidget( Widget* theWidget );
		void Resize( int x, int y, int width, int height );
		void Resize( const Rect& frame ) { super::Resize( frame ); }

		Widget* GetClientWidget();
		
		void ClientSizeChanged();
		
        virtual void TouchBegan( const Sexy::Touch& touch );
        virtual void TouchMoved( const Sexy::Touch& touch );
        virtual void TouchEnded( const Sexy::Touch& touch );
		void TouchesCanceled();

		bool GetIsTrackingTouch();
        void SetListener(ScrollWidgetListener* listener) { mListener = listener; }

		void CancelCurrentScroll();

		void Update();
		void Draw( Graphics* g );
		void DrawProxyWidget( Graphics* g, ProxyWidget* proxyWidget );

		void SetCheckClientWidget(bool check) { mCheckClientWidget = check; }
        
        void SetScrollVelocity(FPoint &point) {mScrollVelocity = point;}
        void SetCircleScroll(bool enable) { mCircleScroll = enable; }
        void SetCircleAdditionWidth(int addWidth) { mCircleAdditionWidth = addWidth;}
        void CircleSetScrollOffset( FPoint anOffset, bool animated );
        void CircleTouchMotion( FPoint delta );
        
	private:
		void CheckClientWidget();
		
	protected:
		
		void Init( ScrollWidgetListener* listener );
		void SnapToPage();
		void TouchMotion( const Sexy::Touch& touch );
		Widget* GetClientWidgetAt( const Sexy::Touch& touch, Touch& o_transformedTouch );
		
		struct Overlay
		{
			Image* image;
			Point offset;
		};
		typedef std::vector< Overlay > Overlays;
		
		ScrollWidgetListener* mListener;
		Widget* mClient;
		Widget* mClientLastDown;
		PageControl* mPageControl;
		ProxyWidget* mIndicatorsProxy;
		Image* mIndicatorsImage;
		Image* mIndicatorsBackgroundImage;
		Image* mBackgroundImage;
		bool mFillBackground;
		Overlays mOverlays;
		bool mDrawOverlays;
		
		Alignment mAlignX, mAlignY;
		ScrollMode mScrollMode;
		Insets mScrollInsets;
		FPoint mScrollTarget;
		FPoint mScrollOffset;
		FPoint mScrollVelocity;
		FPoint mScrollTouchReference;
		FPoint mScrollOffsetReference;
		int32 mScrollTouchID;
		bool mScrollForcePassThrough;
		bool mBounceEnabled;
		bool mPagingEnabled;
		bool mIndicatorsEnabled;
		Insets mIndicatorsInsets;
		int mIndicatorsFlashTimer;
		float mIndicatorsOpacity;
		int mCurrentPageHorizontal;
		int mCurrentPageVertical;
		bool mSeekScrollTarget;
		bool mScrollTracking;
		double mScrollLastTimestamp;
		float mThresholdScale;
		float mTimeDTForScrolling;
        FPoint mScrollDragThreshold;
        bool mWasPreviouslyScrollingToTarget;
		
		void CacheDerivedValues();
		
		FPoint mScrollMin;
		FPoint mScrollMax;
		FPoint mPageSize;
		ScrollMode mScrollPractical;
		int mPageCountHorizontal;
		int mPageCountVertical;
		bool mCheckClientWidget;
		bool mClientWidgetChecked;
        
        ScrollSnapper* mScrollSnapper;
		
		bool mCircleScroll;
        int mCircleAdditionWidth;
	};
}

#endif
