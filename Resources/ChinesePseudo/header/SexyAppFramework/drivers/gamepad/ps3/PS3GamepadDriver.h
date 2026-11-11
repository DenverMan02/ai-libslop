#ifndef PS3GAMEPADDRIVER_H_INCLUDED
#define PS3GAMEPADDRIVER_H_INCLUDED

#include "drivers/gamepad/BaseGamepadDriver.h"

#include "cell/Pad.h"

#define NUM_GAMEPADS 4

namespace Sexy
{

	class PS3Gamepad : public BaseGamepad
	{
	public:
		PS3Gamepad(SexyAppBase* theApp,int theGamepadIndex);
		virtual ~PS3Gamepad();

		virtual void Update();

		virtual void AddRumbleEffect( float theLeft, float theRight, float theFadeTime );
	protected:
		inline void UpdateButtonStateDigital( const GamepadButton button, const uint16_t state );
		inline void UpdateButtonStateAnalog( const GamepadButton button, const uint16_t state );
		inline void UpdateAxisState( const GamepadAxis xAxis, const GamepadAxis yAxis, const uint16_t xState, const uint16_t yState );
		inline void UpdateVirtualDpad( const GamepadButton button );
	private:
		CellPadData mInputState;
		uint32 m_gamepad_masks[_GAMEPAD_BUTTON_NUM];

		bool mHasRumble;
		float mRumble[CELL_PAD_ACTUATOR_MAX];
		float mRumbleFadeTime, mRumbleFadeTimer;
	};

	class PS3GamepadDriver : public IGamepadDriver
	{
	public:
		PS3GamepadDriver();
		virtual ~PS3GamepadDriver();

		virtual bool				InitGamepadDriver(SexyAppBase*);
		
		virtual IGamepad*			GetGamepad(int theIndex);
		virtual void				Update();
	private:
		PS3Gamepad* mGamepads[NUM_GAMEPADS];
	};
}

#endif
