#include <string>

#ifndef SexyAppFramework_Prime_UnhandledExceptionHandler_h
#define SexyAppFramework_Prime_UnhandledExceptionHandler_h

namespace Sexy {
    class UnhandledExceptionHandler {
      
    public:
        static void HandleException(const char* exception, const char* stacktrace);
    };
};

#endif
