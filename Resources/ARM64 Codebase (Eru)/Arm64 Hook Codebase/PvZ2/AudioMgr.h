#pragma once

class AudioMgr
{
public:
    static AudioMgr* GetInstance()
    {
        return *(AudioMgr**)GetActualOffset(0x256A180);
    }

	static void PlayAudio(const SexyString& eventName)
	{
        CallFunc<void>(GetActualOffset(0xA38D18), AudioMgr::GetInstance(), eventName, 0);
	}
};