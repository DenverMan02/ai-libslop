/*
*****************************************************************************
*   SCC:Perforce SCM
*
*   $File:$                      
*
*   $Revision:$
*
*   $DateTime:$
*
*   $Author:$   	  
*
*   $Id:$
*
*****************************************************************************
*
* Description: WinRT Core App Functionality
*
*****************************************************************************
*
* The following text and routines are proprietary and protected by the
* following copyright:
*
* PopCap Games
* 2401 4th Ave, Suite 300
* Seattle, WA 98121
*
*****************************************************************************
*
* History-
*
* 06.23.12 	_SCL_	Initial Version
*
*****************************************************************************
*/

#ifndef __WINRT_APP_CORE__
#define __WINRT_APP_CORE__ 

#include <wrl/client.h>

namespace Sexy
{
	ref class WinRTAppCore sealed : public Windows::ApplicationModel::Core::IFrameworkView
	{
	public:
		WinRTAppCore();
		
		// IFrameworkView Methods
		virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
		virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
		virtual void Load(Platform::String^ entryPoint);
		virtual void Run();
		virtual void Uninitialize();
			

	protected:
		// Event Handlers
		void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
		void OnLogicalDpiChanged(Platform::Object^ sender);
		void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
		void OnResuming(Platform::Object^ sender, Platform::Object^ args);
		void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);

		void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
		void OnPointerMoved(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
		void OnPointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
		void OnPointerWheelChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
		
		void OnKeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);
		void OnKeyUp(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);
				
	private:
		bool	m_bWindowClosed;
	};

	ref class WinRTAppSourceD3D sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
	{
	public:
		virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
	};

};

#endif
//********************************************************** end-of-include *







