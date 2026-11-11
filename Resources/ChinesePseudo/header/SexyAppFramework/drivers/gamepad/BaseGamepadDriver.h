#ifndef BASEGAMEPADDRIVER_H_INCLUDED
#define BASEGAMEPADDRIVER_H_INCLUDED

#include "IGamepadDriver.h"

namespace Sexy
{
	class GamepadData
	{
	public:
		//TODO:  expose repeat rates to games
		static const int PAD_REPEAT_MAX = 17;
		static const int DEFAULT_REPEAT_MAX = 100;


		GamepadData()
		{
			for (int i=0; i<_GAMEPAD_AXIS_NUM; i++)
			{
				mAxis[i] = 0.0f;
			}

			for (int i=0; i<_GAMEPAD_BUTTON_NUM; i++)
			{
				mButton[i] = false;
				mButtonPressure[i] = 0.0f;
				mLastRepeat[i] = 0;
				mStartRepeat[i] = 0;
				mRepeatMax[i] = DEFAULT_REPEAT_MAX;
			}

			mRepeatMax[GAMEPAD_BUTTON_UP]   = PAD_REPEAT_MAX;
			mRepeatMax[GAMEPAD_BUTTON_DOWN] = PAD_REPEAT_MAX;
			mRepeatMax[GAMEPAD_BUTTON_LEFT] = PAD_REPEAT_MAX;
			mRepeatMax[GAMEPAD_BUTTON_RIGHT]= PAD_REPEAT_MAX;

			mRepeatMax[GAMEPAD_BUTTON_DPAD_UP]   = PAD_REPEAT_MAX;
			mRepeatMax[GAMEPAD_BUTTON_DPAD_DOWN] = PAD_REPEAT_MAX;
			mRepeatMax[GAMEPAD_BUTTON_DPAD_LEFT] = PAD_REPEAT_MAX;
			mRepeatMax[GAMEPAD_BUTTON_DPAD_RIGHT]= PAD_REPEAT_MAX;

			mConnected = false;

		};

		bool mConnected;
		float mAxis[_GAMEPAD_AXIS_NUM];

		bool mButton[_GAMEPAD_BUTTON_NUM];
		float mButtonPressure[_GAMEPAD_BUTTON_NUM];

		int	mLastRepeat[_GAMEPAD_BUTTON_NUM];
		int	mStartRepeat[_GAMEPAD_BUTTON_NUM];
		int	mRepeatMax[_GAMEPAD_BUTTON_NUM];
	};

	class BaseGamepad : public IGamepad
	{
	protected:
		BaseGamepad(SexyAppBase* theApp, int theGamepadIndex);

	public:
		virtual ~BaseGamepad();

		virtual bool		IsConnected();

		int					GetGamepadIndex();

		virtual bool		IsButtonDown(GamepadButton button);
		virtual float		GetButtonPressure(GamepadButton button);

		virtual float		GetAxisXPosition();
		virtual float		GetAxisYPosition();
		
		virtual float		GetRightAxisXPosition();
		virtual float		GetRightAxisYPosition();

		virtual void		Update();
		

		virtual void		AddRumbleEffect( float theLeft, float theRight, float theFadeTime );
	protected:

		void				HandleButtonDown( GamepadButton theButton, uint32 flags );
		void				HandleButtonUp( GamepadButton theButton, uint32 flags );
		void				HandleAxisMove( GamepadAxis theButton, float value );
	
	protected:
		int				mGamepadIndex;
		SexyAppBase*	mApp;
		GamepadData		mGamepadData;
	};

}

#endif
