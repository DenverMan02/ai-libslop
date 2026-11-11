#ifndef NULLGAMEPADDRIVER_H_INCLUDED
#define NULLGAMEPADDRIVER_H_INCLUDED

#include "IGamepadDriver.h"

namespace Sexy
{
	class NullGamepad : public IGamepad
	{
	public:
		NullGamepad(SexyAppBase* theApp, int theGamepadIndex) { mApp = theApp; mGamepadIndex = theGamepadIndex; }
		virtual ~NullGamepad() {}

		virtual bool		IsConnected() { return false; }

		int					GetGamepadIndex() { return mGamepadIndex; }

		virtual bool		IsButtonDown(GamepadButton button) { return false; }
		virtual float		GetButtonPressure(GamepadButton button) { return 0.0f; }

		virtual float		GetAxisXPosition() { return 0.0f; }
		virtual float		GetAxisYPosition() { return 0.0f; }
		
		virtual float		GetRightAxisXPosition() { return 0.0f; }
		virtual float		GetRightAxisYPosition() { return 0.0f; }

		virtual void		Update() {  }
		

		virtual void		AddRumbleEffect( float theLeft, float theRight, float theFadeTime ) {}

	protected:
		int				mGamepadIndex;
		SexyAppBase*	mApp;
	};

	class NullGamepadDriver : public IGamepadDriver
	{
	public:
		NullGamepadDriver();
		virtual ~NullGamepadDriver();

		virtual bool				InitGamepadDriver(SexyAppBase*);
		
		virtual IGamepad*			GetGamepad(int theIndex);
		virtual void				Update();
	private:
		NullGamepad* mGamepads[4];
	};

}

#endif