/////////////////////////////////////////////////////////////////////////////
// eathread_sync_armgcc.h
//
// Copyright (c) 2010, Electronic Arts Inc. All rights reserved.
//
// Functionality related to memory and code generation synchronization.
//
// Created by Scott Graham
/////////////////////////////////////////////////////////////////////////////


#ifndef EATHREAD_ARMGCC_EATHREAD_SYNC_ARMGCC_H
#define EATHREAD_ARMGCC_EATHREAD_SYNC_ARMGCC_H


#ifndef INCLUDED_eabase_H
    #include <EABase/eabase.h>
#endif


#if defined(EA_PROCESSOR_ARM) && defined(EA_COMPILER_GNUC)
    #define EA_THREAD_SYNC_IMPLEMENTED

    // Warning! This is a non-SMP ARM only.
    //
    // Usage of DMB will be necessary once we're targeting SMP ARM.

    #define EA_TARGET_SMP 0


    #ifndef EA_MEMORY_BARRIERS_REQUIRED
        #define EA_MEMORY_BARRIERS_REQUIRED 0
    #endif


    #define EAProcessorPause()

    #if EA_MEMORY_BARRIERS_REQUIRED
        #error TODO
    #else
        #define EAReadBarrier()      EACompilerMemoryBarrier()
        #define EAWriteBarrier()     EACompilerMemoryBarrier()
        #define EAReadWriteBarrier() EACompilerMemoryBarrier()
    #endif


    // EACompilerMemoryBarrier
    #if defined(EA_COMPILER_GNUC)
        #define EACompilerMemoryBarrier() __asm__ __volatile__ ("" : : : "memory")
    #else
        #error TODO
    #endif


#endif


#endif
