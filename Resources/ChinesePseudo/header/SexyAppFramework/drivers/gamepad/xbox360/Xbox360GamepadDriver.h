#ifndef XBOX360GAMEPADDRIVER_H_INCLUDED
#define XBOX360GAMEPADDRIVER_H_INCLUDED

#include "drivers/gamepad/BaseGamepadDriver.h"
#if defined (_XBOX) || defined (_XENON)    
#include <xtl.h>
#elif defined (_WIN32)
#include <XInput.h>
#endif

namespace Sexy
{
	class Xbox360Gamepad : public BaseGamepad
	{
	public:
		Xbox360Gamepad(SexyAppBase* theApp,int theGamepadIndex);
		virtual ~Xbox360Gamepad();

		virtual void		Update();
		

		virtual void		AddRumbleEffect( float theLeft, float theRight, float theFadeTime );
	protected:
		//system features...
		uint32 m_gamepad_masks[_GAMEPAD_BUTTON_NUM];
		XINPUT_STATE mInputState;

		float	mRumbleLeft, mRumbleRight, mRumbleFadeTime, mRumbleFadeTimer;
	};

	class Xbox360GamepadDriver : public IGamepadDriver
	{
	public:
		Xbox360GamepadDriver();
		virtual ~Xbox360GamepadDriver();

		virtual bool				InitGamepadDriver(SexyAppBase*);
		
		virtual IGamepad*			GetGamepad(int theIndex);
		virtual void				Update();
	private:
		Xbox360Gamepad* mGamepads[4];
	};
}

#endif