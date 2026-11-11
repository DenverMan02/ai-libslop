
#pragma once
#include "Widget.h"

namespace Sexy
{
	class ProxyWidget;
	
	class ProxyWidgetListener
	{
	public:
		virtual void DrawProxyWidget( Graphics* g, ProxyWidget* proxyWidget ) = 0;
	};
	
	class ProxyWidget : public Widget
	{
		typedef Widget super;
		ProxyWidgetListener* mListener;
	public:
		ProxyWidget( ProxyWidgetListener* listener );
		void Draw( Graphics* g );
	};
	
}

