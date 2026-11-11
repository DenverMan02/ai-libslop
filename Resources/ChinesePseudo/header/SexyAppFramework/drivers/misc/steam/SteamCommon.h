#ifndef STEAMCOMMON_H_INCLUDED
#define STEAMCOMMON_H_INCLUDED

namespace Sexy
{
	class SteamAPI
	{
	public:
		static bool Init();
		static bool IsConnected(){ return mConnected; };

		static void SteamAPIWarningMessageHook( int severity, const char *err );

	private:
		static bool mConnected;
	};
};

#endif
