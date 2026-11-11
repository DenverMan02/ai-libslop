#include "MemUtils.h"

#include <And64InlineHook/And64InlineHook.hpp>

uintptr_t g_libAddress = NULL;

uintptr_t GetLibraryAddress(const char* libName) {
    FILE* fp = fopen("/proc/self/maps", "rt");
    if (fp == nullptr) {
        perror("fopen");
        return 0;
    }

    uintptr_t addr = 0;
    char line[1024];

    while (fgets(line, sizeof(line), fp) != nullptr) {
        if (strstr(line, libName) != nullptr) {
            addr = strtoul(line, nullptr, 16);
            break;
        }
    }

    fclose(fp);
    return addr;
}


uintptr_t GetActualOffset(uintptr_t offset)
{
    if (g_libAddress == 0)
    {
        g_libAddress = GetLibraryAddress("libPVZ2.so");
    }
    return g_libAddress + offset;
}

uintptr_t GetOriginalOffset(uintptr_t actualOffset) {
    if (g_libAddress == 0)
    {
        g_libAddress = GetLibraryAddress("libPVZ2.so");
    }
    return actualOffset - g_libAddress;
}

uintptr_t* GetMemberPtr(void* obj, uintptr_t memberOffset)
{
    uintptr_t member = *(uintptr_t*)(*(int*)obj + memberOffset);
    return &member;
}

void PVZ2HookFunction(uintptr_t offset, void* replace, void** result)
{
    A64HookFunction((void*)GetActualOffset(offset), replace, result);
}

void* CopyVFTable(int vftableAddr, int numVFuncs)
{
    int size = numVFuncs * sizeof(int);
    void* vftableCopy = malloc(size);
    memcpy(vftableCopy, (const void*)vftableAddr, size);
    return vftableCopy;
}

void CopyVFTable(void* dest, intptr_t vftableAddr, int numVFuncsToCopy)
{
    int size = numVFuncsToCopy * sizeof(int);
    memcpy(dest, (const void*)vftableAddr, size);
}

void PatchVFTable(void* vftable, void* funcAddr, int index)
{
    ((reinterpret_cast<void**>(vftable))[index]) = funcAddr;
}

void* CreateChildVFTable(int vFuncsCount, intptr_t parentVftable, int nuMVFuncsToCopy)
{
    int size = vFuncsCount * sizeof(int);
    void* childVftable = malloc(size);
    CopyVFTable(childVftable, parentVftable, nuMVFuncsToCopy);

    return childVftable;
}

void SetVFTable(void* obj, uintptr_t newVftablePtr)
{
    *reinterpret_cast<int*>(uintptr_t(obj)) = newVftablePtr;
}

void* GetVirtualFunc(void* obj, int index)
{
    void** vtable = *reinterpret_cast<void***>(obj);
    return vtable[index];
}