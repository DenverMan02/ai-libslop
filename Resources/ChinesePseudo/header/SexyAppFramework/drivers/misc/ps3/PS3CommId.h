#ifndef PS3COMMID_H_INCLUDED
#define PS3COMMID_H_INCLUDED

#include <sysutil/sysutil_gamecontent.h>
#include <np.h>

namespace Sexy
{
	extern const char gPS3TitleId[CELL_GAME_SYSP_TITLEID_SIZE];
	extern const SceNpCommunicationId gPS3CommId;
	extern const SceNpCommunicationSignature gPS3CommSignature;
	extern const SceNpCommunicationPassphrase gPS3CommPassphrase;
}

#endif
