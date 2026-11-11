#ifndef IPHONEOSDIAGDRIVER_H_INCLUDED
#define IPHONEOSDIAGDRIVER_H_INCLUDED

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
	
    bool SystemVersionGreaterThanOrEqualTo(std::string v);
    
	class iPhoneOSDiagDriver : public BaseDiagDriver
	{
	public:
		iPhoneOSDiagDriver();
		~iPhoneOSDiagDriver();

		bool Init();
		void Update();

		const char* GetInfoString(EInfoStringType inType);
        double GetInfoNumber(EInfoNumberType inType);
        const versionNums VersionStringToInts();
		
		HHardwareBreakpoint SetHardwareBreakpoint(EHardwareBreakpointType inType, void* inAddr, int inSizeBytes);
		bool ClearHardwareBreakpoint(HHardwareBreakpoint inHandle);

		int GetCallStack(void** outCallStack, int inNumStackElements);
		bool GetTextForCallStack(void** inCallStack, int inNumStackElements, std::string* ioStrings);
		
        int GetFPS();
        uint64 GetMemoryUsed();
		uint64 GetMemoryAvailable();
	protected:
		const char* GetInfoStringFromSysCtlByName( const char* name );
		const char* GetPrimaryMACAddress();
	};
};

#endif
