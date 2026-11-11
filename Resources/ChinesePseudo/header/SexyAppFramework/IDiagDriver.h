#ifndef IDIAGDRIVER_H_INCLUDED
#define IDIAGDRIVER_H_INCLUDED

#include <string>

namespace Sexy
{
	/*
		IDiagDriver - Diagnostics driver interface (call stacks, hardware breakpoints, etc.)
	*/
	class IDiagDriver
	{
	public:
		enum EInfoStringType
		{
			INFO_OSVersion,
			INFO_HardwareModel,
			INFO_DeviceID,
		};
		
        enum EInfoNumberType
        {
            INFO_FPS,
            INFO_MemoryAvailable,
            INFO_MemoryUsed,  
        };

		enum EHardwareBreakpointType
		{
			HWBREAK_Code,
			HWBREAK_Data_ReadWrite,
			HWBREAK_Data_Write,
		};

		typedef void* HHardwareBreakpoint;
        
        typedef struct
        {
            int major;
            int minor;
            int bugFix;
        } versionNums;

	public:
		static IDiagDriver* CreateDiagDriver();
		virtual ~IDiagDriver() {}

		virtual bool Init() = 0;
		virtual void Update() = 0;

		/*
			GetInfoString
		 
			Retrieve some information about the system.  Returns NULL if
			the platform does not support the requested string.  Otherwise
			returns a pointer to a string that will remain valid until the
			next call to GetInfoString.  Callers should make their own copy
			of the string for future use.
		*/
		virtual const char* GetInfoString(EInfoStringType inType) = 0;

		/*
			GetInfoStringSafe
		 
			Returns the same string provided by GetInfoString, except in the
			case where GetInfoString returns NULL this method returns an
			empty string.
		*/
		virtual const char* GetInfoStringSafe(EInfoStringType inType) = 0;
        
        /*
         GetInfoNumber
         
         Same concept as GetInfoString, but returns a double or 0.0 if the implementation is not found.
         
         INFO_FPS: Get the platform specific frames per second for the running game. 
         The platform app driver will be responsible for implementing the FPS
         calculation.
         
         INFO_MemoryAvailable:Get the amount of physical memory available.
         This will be platform specific and may inconsistent among platforms.
         
         INFO_MemoryUsed: Get the amount of physical memory currently being used by the running game.
         This will be platform specific and may inconsistent among platforms.
         */
        virtual double GetInfoNumber(EInfoNumberType inType) = 0;
        
		/*
			SetHardwareBreakpoint
			
			Sets a code or data breakpoint of the given size on the given
			address; the breakpoint will fire whenever the data of the given
			size at that address is executed, read, or written (depending on
			the breakpoint type).  inSizeBytes must be 1, 2, 4, or 8.  Returns
			a handle which can be subsequently passed to ClearHardwareBreakpoint.
		*/
		virtual HHardwareBreakpoint SetHardwareBreakpoint(EHardwareBreakpointType inType, void* inAddr, int inSizeBytes) = 0;

		/*
			ClearHardwareBreakpoint
			
			Called to a remove a breakpoint previously established
			by SetHardwareBreakpoint.
		*/
		virtual bool ClearHardwareBreakpoint(HHardwareBreakpoint inHandle) = 0;
	
		/*
			GetCallStack

			Get a call stack for the current thread.  Takes an array of
			void* to write the call stack addresses to, and the number of
			desired stack elements (which the array must be able to support).
			Returns the actual number of elements written into the call stack
			array (potentially zero if the stack could not be retrieved).
		*/
		virtual int GetCallStack(void** outCallStack, int inNumStackElements) = 0;

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
		virtual bool GetTextForCallStack(void** inCallStack, int inNumStackElements, std::string* ioStrings) = 0;
	};
}

#endif