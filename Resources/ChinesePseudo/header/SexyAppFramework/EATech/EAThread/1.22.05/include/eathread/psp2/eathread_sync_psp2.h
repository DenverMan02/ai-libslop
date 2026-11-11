/////////////////////////////////////////////////////////////////////////////
// eathread_sync_psp2.h
//
// Copyright (c) Electronic Arts Inc. All rights reserved.
//
// Functionality related to memory and code generation synchronization.
/////////////////////////////////////////////////////////////////////////////

#ifndef EATHREAD_PSP2_EATHREAD_SYNC_PSP2_H
#define EATHREAD_PSP2_EATHREAD_SYNC_PSP2_H

#include <kernel.h>

#ifndef INCLUDED_eabase_H
    #include <EABase/eabase.h>
#endif


#if defined(EA_PLATFORM_PSP2)
    #define EA_THREAD_SYNC_IMPLEMENTED

    #define EA_TARGET_SMP 1

    #ifndef EA_MEMORY_BARRIERS_REQUIRED
        #define EA_MEMORY_BARRIERS_REQUIRED 1
    #endif

    #define EAProcessorPause() __builtin_yield()

    #if EA_MEMORY_BARRIERS_REQUIRED
        #define EAReadBarrier()      __builtin_dmb()
        #define EAWriteBarrier()     __builtin_dmb()
        #define EAReadWriteBarrier() __builtin_dmb()
    #endif


    // EACompilerMemoryBarrier
    #define EACompilerMemoryBarrier() 
#endif


#endif
