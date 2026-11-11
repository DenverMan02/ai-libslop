#ifndef WINDOWSDIAGDRIVER_H_INCLUDED
#define WINDOWSDIAGDRIVER_H_INCLUDED

#include "Common.h"
#include "drivers/diag/BaseDiagDriver.h"
#include <iphlpapi.h>

namespace Sexy
{
	class WindowsDiagDriver : public BaseDiagDriver
	{
	private:
		bool mLoadedImageHelp;
		typedef DWORD (WINAPI *GetAdaptersInfoFunc)(PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen);
		GetAdaptersInfoFunc mGetAdaptersInfo;
		HMODULE mIPHlpAPI;

		const char* GetFirstAdapterAddress();
		const char* GetOSVersionString();
	public:
		WindowsDiagDriver();
		~WindowsDiagDriver();

		bool Init();
		void Update();

		const char* GetInfoString(EInfoStringType inType);
		double GetInfoNumber(EInfoNumberType inType);

		HHardwareBreakpoint SetHardwareBreakpoint(EHardwareBreakpointType inType, void* inAddr, int inSizeBytes);
		bool ClearHardwareBreakpoint(HHardwareBreakpoint inHandle);

		int GetCallStack(void** outCallStack, int inNumStackElements);
		bool GetTextForCallStack(void** inCallStack, int inNumStackElements, std::string* ioStrings);
	};
};

#endif
