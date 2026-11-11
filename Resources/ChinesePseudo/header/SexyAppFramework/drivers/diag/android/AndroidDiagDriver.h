#ifndef ANDROIDDIAGDRIVER_H_INCLUDED
#define ANDROIDDIAGDRIVER_H_INCLUDED

#include "Common.h"
#include "drivers/diag/BaseDiagDriver.h"

namespace Sexy
{
	/**
	 * Implemented in iPhoneOSDiagHelper.mm
	 * Returns a temporary C string that will be cleaned up by the innermost
	 * enclosing NSAutoreleasePool, so make your copy immediately.
	 */
//	const char* NSProcessInfoOperatingSystemVersionString();
	
	class AndroidDiagDriver : public BaseDiagDriver
	{
	public:
		AndroidDiagDriver();
		~AndroidDiagDriver();

		typedef void* HHardwareBreakpoint;

	public:
		static IDiagDriver* CreateDiagDriver();

		virtual bool Init();
		virtual void Update();

		/*
			GetInfoString
		 
			Retrieve some information about the system.  Returns NULL if
			the platform does not support the requested string.  Otherwise
			returns a pointer to a string that will remain valid until the
			next call to GetInfoString.  Callers should make their own copy
			of the string for future use.
		*/
		virtual const char* GetInfoString(EInfoStringType inType);


		virtual double GetInfoNumber(EInfoNumberType inType);	//PVZ2_CHINESE

		/*
			SetHardwareBreakpoint
			
			Sets a code or data breakpoint of the given size on the given
			address; the breakpoint will fire whenever the data of the given
			size at that address is executed, read, or written (depending on
			the breakpoint type).  inSizeBytes must be 1, 2, 4, or 8.  Returns
			a handle which can be subsequently passed to ClearHardwareBreakpoint.
		*/
		virtual HHardwareBreakpoint SetHardwareBreakpoint(EHardwareBreakpointType inType, void* inAddr, int inSizeBytes);

		/*
			ClearHardwareBreakpoint
			
			Called to a remove a breakpoint previously established
			by SetHardwareBreakpoint.
		*/
		virtual bool ClearHardwareBreakpoint(HHardwareBreakpoint inHandle);
	
		/*
			GetCallStack

			Get a call stack for the current thread.  Takes an array of
			void* to write the call stack addresses to, and the number of
			desired stack elements (which the array must be able to support).
			Returns the actual number of elements written into the call stack
			array (potentially zero if the stack could not be retrieved).
		*/
		virtual int GetCallStack(void** outCallStack, int inNumStackElements);

		/*
			GetTextForCallStack

			Get human-readable text for the symbol addresses provided by
			GetCallStack.  Depending on the platform, this may include things
			like source code identifiers, source filename and line number,
			and so on.  The ioStrings array should hold inNumStackElements empty
			strings, which will be modified to hold the actual call stack text.
			Returns true if text was written, false if not.

			IMPORTANT: the exact syntax of this text is platform-specific and is
			only intended for human readability, not for machine parsing; please
			do not expect the output text from this method to follow any type of
			rigid grammar.
		*/
		virtual bool GetTextForCallStack(void** inCallStack, int inNumStackElements, std::string* ioStrings);

	};
};

#endif // ANDROIDDIAGDRIVER_H_INCLUDED
