#ifndef MACOSXDIAGDRIVER_H_INCLUDED
#define MACOSXDIAGDRIVER_H_INCLUDED

#include "Common.h"
#include "drivers/diag/BaseDiagDriver.h"

namespace Sexy
{
	/**
	 * Implemented in iPhoneOSDiagHelper.mm
	 * Returns a temporary C string that will be cleaned up by the innermost
	 * enclosing NSAutoreleasePool, so make your copy immediately.
	 */
	const char* NSProcessInfoOperatingSystemVersionString();
	
	class MacosxDiagDriver : public BaseDiagDriver
	{
	public:
		MacosxDiagDriver();
		~MacosxDiagDriver();

		bool Init();
		void Update();

		const char* GetInfoString(EInfoStringType inType);
        double GetInfoNumber(EInfoNumberType inType);
		
		HHardwareBreakpoint SetHardwareBreakpoint(EHardwareBreakpointType inType, void* inAddr, int inSizeBytes);
		bool ClearHardwareBreakpoint(HHardwareBreakpoint inHandle);

		int GetCallStack(void** outCallStack, int inNumStackElements);
		bool GetTextForCallStack(void** inCallStack, int inNumStackElements, std::string* ioStrings);
	protected:
		const char* GetInfoStringFromSysCtlByName( const char* name );
		const char* GetPrimaryMACAddress();
	};
};

#endif
