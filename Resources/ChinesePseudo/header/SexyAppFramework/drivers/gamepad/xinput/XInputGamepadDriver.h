#ifndef XINPUTGAMEPADDRIVER_H_INCLUDED
#define XINPUTGAMEPADDRIVER_H_INCLUDED

#include "drivers/gamepad/BaseGamepadDriver.h"

#if defined (HOST_XBOX360)
#include <xtl.h>
#elif defined (HOST_WINDOWS) || defined (WINRT_CLUSTER)
#include <XInput.h>
#endif

namespace Sexy
{
	class XInputGamepad : public BaseGamepad
	{
	public:
		XInputGamepad(SexyAppBase* theApp,int theGamepadIndex);
		virtual ~XInputGamepad();

		virtual void Update();
		virtual void AddRumbleEffect( float theLeft, float theRight, float theFadeTime );

	protected:
		//system features...
		uint32 m_gamepad_masks[_GAMEPAD_BUTTON_NUM];
		XINPUT_STATE mInputState;

		float mRumbleLeft, mRumbleRight, mRumbleFadeTime, mRumbleFadeTimer;
	};

	class XInputGamepadDriver : public IGamepadDriver
	{
	public:
		XInputGamepadDriver();
		virtual ~XInputGamepadDriver();

		virtual bool InitGamepadDriver(SexyAppBase*);
		
		virtual IGamepad* GetGamepad(int theIndex);
		virtual void Update();
	protected:
		friend class XInputGamepad;

		//xinput api function pointers
		#if !defined(WINRT_DESKTOP) && !defined(WINRT_PHONE)
		typedef DWORD (WINAPI *_XInputGetState) ( DWORD dwUserIndex, XINPUT_STATE* pState );
		typedef DWORD (WINAPI *_XInputSetState) ( DWORD dwUserIndex, XINPUT_VIBRATION* pVibration );
		static _XInputGetState pfXInputGetState;
		static _XInputSetState pfXInputSetState;
		#endif

	private:
		bool mEnabled;
		XInputGamepad* mGamepads[4];

#ifdef HOST_WINDOWS
		HMODULE mHmod;
#endif
	};
}

#endif
