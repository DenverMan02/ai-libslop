/////////////////////////////////////////////////////////////////////////////
// eathread_sync_powerpc.h
//
// Copyright (c) 2003, Electronic Arts Inc. All rights reserved.
//
// Functionality related to memory and code generation synchronization.
//
// Created by Paul Pedriana, Maxis
/////////////////////////////////////////////////////////////////////////////


#ifndef EATHREAD_POWERPC_EATHREAD_SYNC_POWERPC_H
#define EATHREAD_POWERPC_EATHREAD_SYNC_POWERPC_H


#ifndef INCLUDED_eabase_H
    #include <EABase/eabase.h>
#endif
#if defined(EA_PLATFORM_PS3)
    #include <ppu_intrinsics.h>
#elif defined(EA_PLATFORM_XENON)
    #include <ppcintrinsics.h>
#endif


// As of this writing, EA_PROCESSOR_POWERPC isn't yet supported by eabase, though it 
// may be so in the eventual future. For the time being, GCC and Metrowerks support 
// the __PPC__ define, so it will do for now.
#if defined(EA_PROCESSOR_POWERPC) || defined(__PPC__) || defined(__PPCGEKKO__) || defined(__powerpc__) || defined(__powerpc64__)
    #define EA_THREAD_SYNC_IMPLEMENTED

    ////////////////////////////////////////////////////////////////////////////
    // IBM PowerPC documentation
    //
    // http://www.ibm.com/chips/products/powerpc/newsletter/apr2001/design-h-t.html
    // 
    // "Synchronization Instructions
    // 
    // Commonly misunderstood PowerPC instructions are those that perform 
    // synchronization. These instructions include:
    // 
    // - Enforce In/Order Execution of I/O (eieio) - This instruction is for 
    //    data accesses to guarantee that loads and stores complete with respect 
    //    to one another. Since PowerPC defines a weakly ordered storage model 
    //    in which loads and stores can complete out of order, this instruction 
    //    exists to guarantee ordering where necessary.
    //  
    // - Synchronize (sync) - This instruction guarantees that the preceding 
    //    instructions complete before the sync completes. This instruction is 
    //    useful for guaranteeing load/store access completion. For example, 
    //    a sync may be used when writing memory mapped I/O registers to a 
    //    slow device before making further access to the device.
    //
    // - Instruction Synchronize (isync) - This instruction provides ordering 
    //    for all effects of all instructions executed by the processor. It is 
    //    used to synchronize the instruction context, such as memory translation, 
    //    endianness, cache coherency, etc. Instruction pipelines are flushed when 
    //    an isync is performed, and the next instruction is fetched in the new 
    //    context. This instruction is useful for self-modifying code.
    //
    // IBM doesn't recommend using eieio for ordering accesses to cache-enabled memory. 
    // It should only be used for ordering accesses to cache-inhibited and memory mapped I/O. 
    // For ordering accesses to cached memory *only* you should use lwsync. 
    // For ordering accesses between a mixture of cached and uncached memory 
    // (e.g. updating GPU push buffers) you should use the heavyweight sync instruction.
    ////////////////////////////////////////////////////////////////////////////


    #ifndef EA_TARGET_SMP
        // In this case we define EA_TARGET_SMP to be true. The reason for this is that most 
        // applications that users of this code are likely to write are going to be executables
        // which run properly on any system, be it multiprocessing or not.
        #define EA_TARGET_SMP 1
    #endif

    #ifndef EA_MEMORY_BARRIERS_REQUIRED
        #define EA_MEMORY_BARRIERS_REQUIRED 1
    #endif


    // EAProcessorPause
    // The PowerPC doesn't have a processor pause or rest instruction, but some implementations
    // of it have the dbcyc pseudo-instruction.
    #if defined(EA_PLATFORM_XENON)
        #define EAProcessorPause() YieldProcessor()
    #elif defined(EA_PLATFORM_PS3)
        #define EAProcessorPause() __db16cyc()
    #else
        #define EAProcessorPause()
    #endif

    // EAReadBarrier / EAWriteBarrier / EAReadWriteBarrier
    // A single processor PPC system doesn't need any support for read/write barriers.
    // However, an multiprocessor SMP system needs such support. Most of the time your
    // app will be targeting single processor systems and thus a executing read/write
    // barriers would be a waste of time. So we follow the Linux OS standard of providing
    // a separate build option for SMP and non-SMP in order to allow both to achieve 
    // maximum performance.
    #if EA_MEMORY_BARRIERS_REQUIRED
        #if defined(EA_PLATFORM_XENON)
            // Microsoft uses lwsync both read ("acquire") and write ("release") barriers  
            // on the Xenon (XBox 360) platform). 
            #define EAReadBarrier()      __lwsync()
            #define EAWriteBarrier()     __lwsync() 
            #define EAReadWriteBarrier() __lwsync() 

        #elif defined(__SNC__)
            #define EAReadBarrier()      __builtin_lwsync()
            #define EAWriteBarrier()     __builtin_lwsync()
            #define EAReadWriteBarrier() __builtin_lwsync()

        #else
            // We're following the Linux convention here and noting that the PowerPC architecture 
            // causes large penalties for using sync on MP systems, especially for 64 bit PowerPC.
            // We want to verify that this is the case for the platforms we are interested in.
            // Otherwise, lwsync does much of what sync does with respect to conventional memory synchronization.

            #define EAReadBarrier()      __asm__ __volatile__ ("lwsync" : : : "memory")
            #define EAWriteBarrier()     __asm__ __volatile__ ("lwsync" : : : "memory")
            #define EAReadWriteBarrier() __asm__ __volatile__ ("lwsync" : : : "memory")
        #endif
    #else
        #define EAReadBarrier()      EACompilerMemoryBarrier()
        #define EAWriteBarrier()     EACompilerMemoryBarrier()
        #define EAReadWriteBarrier() EACompilerMemoryBarrier()
    #endif


    // EACompilerMemoryBarrier
    #if defined(EA_PLATFORM_PS3) && defined(__SNC__) && (__SN_VER__ >= 22002)
        #define EACompilerMemoryBarrier() __builtin_fence()  // SN has stated that this acts as intended. It is not the same as a hardware-level barrier (e.g. lwsync).
    #elif defined(EA_PLATFORM_PS3) && defined(__SNC__) && (__SN_VER__ < 22002)
        #define EACompilerMemoryBarrier() __nop()  // __nop is the best we can do for older versions of SNC
    #elif defined(EA_COMPILER_GNUC)
        #define EACompilerMemoryBarrier() __asm__ __volatile__ ("" : : : "memory")
    #elif defined(EA_COMPILER_METROWERKS)
        #define EACompilerMemoryBarrier() // Any way to do this?
    #elif defined(EA_COMPILER_MSVC)
        extern "C" void _ReadWriteBarrier();
        #pragma intrinsic(_ReadWriteBarrier)
        #define EACompilerMemoryBarrier() _ReadWriteBarrier()
    #else
        #define EACompilerMemoryBarrier() // Possibly assert false here?
    #endif


#endif // EA_PROCESSOR_POWERPC, etc.


#endif // EATHREAD_POWERPC_EATHREAD_SYNC_POWERPC_H








