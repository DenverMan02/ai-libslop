#pragma once
#ifndef IGAMEPADDRIVER_H_INCLUDED
#define IGAMEPADDRIVER_H_INCLUDED

namespace Sexy 
{
	class SexyAppBase;


	#define GAMEPAD_PLAYER_MERGED -1

	enum GamepadAxis
	{
		GAMEPAD_AXIS_LSTICK_X = 0,
		GAMEPAD_AXIS_LSTICK_Y,
		GAMEPAD_AXIS_RSTICK_X,
		GAMEPAD_AXIS_RSTICK_Y,
		
		_GAMEPAD_AXIS_NUM,
	};

	enum GamepadButton
	{
		//the DPad and the Left Thumbstick are merged for the sake of the buttons
		GAMEPAD_BUTTON_UP = 0,
		GAMEPAD_BUTTON_DOWN,
		GAMEPAD_BUTTON_LEFT,
		GAMEPAD_BUTTON_RIGHT,
		GAMEPAD_BUTTON_BACK,
		GAMEPAD_BUTTON_START,
		GAMEPAD_BUTTON_A,
		GAMEPAD_BUTTON_B,
		GAMEPAD_BUTTON_X,
		GAMEPAD_BUTTON_Y,
		GAMEPAD_BUTTON_LB,
		GAMEPAD_BUTTON_RB,
		GAMEPAD_BUTTON_LTRIGGER,
		GAMEPAD_BUTTON_RTRIGGER,
		GAMEPAD_BUTTON_LSTICK,
		GAMEPAD_BUTTON_RSTICK,

		GAMEPAD_BUTTON_DPAD_UP,
		GAMEPAD_BUTTON_DPAD_DOWN,
		GAMEPAD_BUTTON_DPAD_LEFT,
		GAMEPAD_BUTTON_DPAD_RIGHT,
		

		_GAMEPAD_BUTTON_NUM,

		//aliases for PS3 controller (in case you want to be obsessive)
		GAMEPAD_BUTTON_PS_CROSS = GAMEPAD_BUTTON_A,
		GAMEPAD_BUTTON_PS_SQUARE = GAMEPAD_BUTTON_X,
		GAMEPAD_BUTTON_PS_CIRCLE = GAMEPAD_BUTTON_B,
		GAMEPAD_BUTTON_PS_TRIANGLE = GAMEPAD_BUTTON_Y,
		GAMEPAD_BUTTON_PS_L1 = GAMEPAD_BUTTON_LB,
		GAMEPAD_BUTTON_PS_L2 = GAMEPAD_BUTTON_LTRIGGER,
		GAMEPAD_BUTTON_PS_L3 = GAMEPAD_BUTTON_LSTICK,
		GAMEPAD_BUTTON_PS_R1 = GAMEPAD_BUTTON_RB,
		GAMEPAD_BUTTON_PS_R2 = GAMEPAD_BUTTON_RTRIGGER,
		GAMEPAD_BUTTON_PS_R3 = GAMEPAD_BUTTON_RSTICK,
		GAMEPAD_BUTTON_PS_START = GAMEPAD_BUTTON_START,
		GAMEPAD_BUTTON_PS_SELECT = GAMEPAD_BUTTON_BACK,

		
	};

	


#define GAMEPAD_BUTTON_REPEAT		0x0001
#define GAMEPAD_BUTTON_IS_DPAD		0x0002
#define GAMEPAD_BUTTON_JUST_BOUND	0x0004
#define GAMEPAD_BUTTON_FROM_CHILD	0x0008 //set if the button press is coming up from a child widget, not the directly focused widget

	


	class IGamepad
	{
	public:
		virtual ~IGamepad()	{}

		virtual bool		IsConnected() = 0;

		virtual int			GetGamepadIndex() = 0;

		virtual bool		IsButtonDown(GamepadButton button) = 0;
		virtual float		GetButtonPressure(GamepadButton button) = 0; //0.0f - 1.0f

		virtual float		GetAxisXPosition() = 0;
		virtual float		GetAxisYPosition() = 0;

//		virtual float		GetAxisXPositionRamped() = 0;
//		virtual float		GetAxisYPositionRamped() = 0;
		
		virtual float		GetRightAxisXPosition() = 0;
		virtual float		GetRightAxisYPosition() = 0;

		virtual void		Update() = 0;
		

		virtual void		AddRumbleEffect( float theLeft, float theRight, float theFadeTime ) = 0;
	};

	class IGamepadDriver
	{
	public:
		static IGamepadDriver*		CreateGamepadDriver();

		virtual ~IGamepadDriver() {}

		virtual bool				InitGamepadDriver(SexyAppBase*) = 0;
		
		virtual IGamepad*			GetGamepad(int theIndex) = 0;
		virtual void				Update() = 0;

	};

};


#endif
