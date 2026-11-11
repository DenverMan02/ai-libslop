
#ifndef SexyAppFramework_Prime_MoreInfoWidget_h
#define SexyAppFramework_Prime_MoreInfoWidget_h

#include "MoreInfoManager.h"
#include "SysFont.h"
#include "RtDelegate.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "drivers/misc/iphoneos/ProxyWidget.h"

namespace Sexy
{
	typedef Delegate1<uint32> InfoPanelPickDelegate;
	
	/**
	 * View widget for an InfoPanel.
	 */
	class InfoPanelWidget
		: public Widget
	{
		typedef Widget super;
		
	public:
		
		InfoPanelWidget( uint32 panelIndex, const InfoPanel* panel, InfoPanelPickDelegate pickDelegate );
		~InfoPanelWidget();
		
		void Draw( Graphics* g );
		
		void TouchBegan( Touch* touch );
		void TouchMoved( Touch* touch );
		void TouchEnded( Touch* touch );
		void TouchesCanceled();
		
		uint32 mPanelIndex;
		InfoPanelPickDelegate mPickDelegate;
		void* mTouchID;
		Point mTouchStart;
		InfoPanel mInfo;
		int mImageX,mImageY; 
	};
	
	/**
	 * A table-like view widget that goes inside the MoreInfoWidget scroll widget
	 */
	class MoreInfoTable
		: public Widget
		, public ButtonListener
	{
		typedef Widget super;
		
	public:
		
		MoreInfoTable();
		~MoreInfoTable();
		
		void Reset();
		void Rebuild( ScrollWidget::ScrollMode scrollMode );
		void PanelPicked( uint32 panelIndex );
	};

	/**
	 *
	 */
	class MoreInfoWidget
		: public ScrollWidget
	{
		typedef ScrollWidget super;

	public:
		
		MoreInfoWidget();
		~MoreInfoWidget();

		void InfoRefreshComplete();
		void InfoRefreshCanceled();
		
		void Resize( int x, int y, int w, int h );
		void Resize( const Rect& frame );
		void Update();
		
		void DrawProxyWidget( Graphics* g, ProxyWidget* proxyWidget );
		virtual void DrawBusy( Graphics* g );
		virtual void DrawFailMessage( Graphics* g );
		void SetVisible(bool v);
	
	protected:
		
		void Rebuild();

		MoreInfoTable* mTable;
	};
	
}

#endif
