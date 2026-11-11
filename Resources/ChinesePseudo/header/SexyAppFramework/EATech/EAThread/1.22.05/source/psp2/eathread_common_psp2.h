#ifndef EATHREAD_COMMON_H
#define EATHREAD_COMMON_H

namespace EA
{
    namespace Thread
    {
        int32_t ConvertToSystemPriority(int32_t priority);
        int32_t ConvertToEAThreadPriority(int32_t systemPriority);
        int32_t ConvertToSystemAffinity(int32_t processor);
        
        // TODO: Check what happens when you pass in a timeout of 0
        static uint32_t ConvertToRelativeTime(const ThreadTime& timeoutAbsolute)
        {
            if (timeoutAbsolute == kTimeoutNone)
            {
                // Do not try to change kTimeoutNone - convert from UINT64_MAX to UINT32_MAX
                return UINT32_MAX;
            }
            else if (timeoutAbsolute == kTimeoutImmediate)
            {
                // Early exit
                return 0;
            }
            else
            {
                int32_t timeoutRelative = static_cast<uint32_t>(timeoutAbsolute - GetThreadTime()) * 1000; // Convert time to milliseconds
                EAT_ASSERT(timeoutRelative >= 0);
                
                if (timeoutRelative < 0)
                {
                    // This occurs if the time had already passed by the time we get to this method
                    timeoutRelative = 0;
                }

                return static_cast<uint32_t>(timeoutRelative);
            }
        }
    }
}

#endif