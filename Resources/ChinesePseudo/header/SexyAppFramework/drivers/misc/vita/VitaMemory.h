#ifndef VITA_MEMORY_H_INCLUDED
#define VITA_MEMORY_H_INCLUDED

#include "Debug.h"
#include <gxm.h>

namespace Sexy
{

// Callback function to allocate memory for the shader patcher
void *patcherHostAlloc(void* userData, uint32_t size);

// Callback function to allocate memory for the shader patcher
void patcherHostFree(void* userData, void *mem);

// Helper function to allocate memory and map it for the GPU
void *graphicsAlloc(SceKernelMemBlockType type, uint32 size, uint32 alignment, uint32 attribs, SceUID *uid);

// Helper function to free memory mapped to the GPU
void graphicsFree(void *mem, SceUID uid);


};
#endif
