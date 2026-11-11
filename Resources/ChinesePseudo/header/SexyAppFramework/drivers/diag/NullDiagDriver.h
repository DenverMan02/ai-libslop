#ifndef NULLDIAGDRIVER_H_INCLUDED
#define NULLDIAGDRIVER_H_INCLUDED

#include "IDiagDriver.h"

namespace Sexy
{
	class NullDiagDriver : public IDiagDriver
	{
	public:
		bool Init() { return true; }
		void Update() {}

		const char* GetInfoString(EInfoStringType inType) { return NULL; }
		const char* GetInfoStringSafe(EInfoStringType inType) { return NULL; }
        
		HHardwareBreakpoint SetHardwareBreakpoint(EHardwareBreakpointType inType, void* inAddr, int inSizeBytes) { return NULL; }
		bool ClearHardwareBreakpoint(HHardwareBreakpoint inHandle) { return true; }
	
		int GetCallStack(void** outCallStack, int inNumStackElements) { return 0; }
		bool GetTextForCallStack(void** inCallStack, int inNumStackElements, std::string* ioStrings) { return false; }
			
		double GetInfoNumber(EInfoNumberType inType) { return 0.0f; }
	};
};

#endif
