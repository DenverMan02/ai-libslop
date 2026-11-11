//#define MEMTRACK_ENABLE

#ifdef MEMTRACK_ENABLE
#include "MemTracker.h"
#include "UnDefineNew.h"

#define new new(__FILE__, __LINE__)
#define malloc(size) (malloc_custom(size, __FILE__, __LINE__))
#define realloc(ptr, size) (realloc_custom(ptr, size, __FILE__, __LINE__))
#define free(p) (free_custom(p))
#endif	// MEMTRACK_ENABLE
