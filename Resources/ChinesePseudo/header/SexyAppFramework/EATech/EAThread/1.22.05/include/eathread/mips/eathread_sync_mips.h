/////////////////////////////////////////////////////////////////////////////
// eathread_sync_mips.h
//
// Copyright (c) 2003, Electronic Arts Inc. All rights reserved.
//
// Functionality related to memory and code generation synchronization.
//
// Created by Paul Pedriana, Maxis
/////////////////////////////////////////////////////////////////////////////


#ifndef EATHREAD_MIPS_EATHREAD_SYNC_MIPS_H
#define EATHREAD_MIPS_EATHREAD_SYNC_MIPS_H


#ifndef INCLUDED_eabase_H
   #include <EABase/eabase.h>
#endif



// As of this writing, EA_PROCESSOR_MIPS isn't yet supported by eabase, though it 
// may be so in the eventual future. For the time being, GCC and Metrowerks support 
// the __MIPS__ define, so it will do for now.
#if defined(EA_PROCESSOR_MIPS) || defined(__mips)
   #define EA_THREAD_SYNC_IMPLEMENTED

   // The R3000 is a MIPS processor used as the PlayStation 2 IO processor.
   // The R4000 is a MIPS processor primarily used for embedded systems.
   // The R5900 (the central PS2 processor) is a processor made by Toshiba but is of the MIPS architecture.
   // The MIPS32 processor is a second generation MIPS4000 which is used for embedded systems including the PlayStation Portable.
   #if defined(EA_PROCESSOR_R3000) || defined(EA_PROCESSOR_R4000) || defined(EA_PROCESSOR_R5900) || defined(EA_PROCESSOR_MIPS32)
      #ifndef EA_TARGET_SMP
        // Otherwise we play it safe and enable SMP support, because applications that use this code would likely be
        // runnable on both single and multiprocessing systems.
        #define EA_TARGET_SMP 1
      #endif

      // EAProcessorPause
      #define EAProcessorPause() // Nothing required.


      // EAReadBarrier / EAWriteBarrier / EAReadWriteBarrier
      // A single processor PPC system doesn't need any support for read/write barriers.
      // However, an multiprocessor SMP system needs such support. Most of the time your
      // app will be targeting single processor systems and thus a executing read/write
      // barriers would be a waste of time. So we follow the Linux OS standard of providing
      // a separate build option for SMP and non-SMP in order to allow both to achieve 
      // maximum performance.
      #if EA_TARGET_SMP
         #define EAReadBarrier()         __mips_sync()   // See below for definition of __mips_sync
         #define EAWriteBarrier()        __mips_sync()
         #define EAReadWriteBarrier()    __mips_sync()   // The Mips R3000 has a writeback buffer that should be flushed here in addition to calling __sync. See 'wbflush' in the Linux kernel source for some information.
      #else
         #define EAReadBarrier()         EACompilerMemoryBarrier()
         #define EAWriteBarrier()        EACompilerMemoryBarrier()
         #define EAReadWriteBarrier()    EACompilerMemoryBarrier()
      #endif

      // EACompilerMemoryBarrier
      #if defined(EA_COMPILER_GNUC) // SN Systems compiler emulates GNUC, and so is covered here.
         #define EACompilerMemoryBarrier() __asm__ __volatile__ ("" : : : "memory")
      #elif defined(EA_COMPILER_METROWERKS)
         #define EACompilerMemoryBarrier() // Any way to do this?
      #else
         #define EACompilerMemoryBarrier() // Possibly `EAT_ASSERT(false)` here?
      #endif


      #if !defined(__mips_sync)
         #if defined(EA_PROCESSOR_R3000)
            // R3000 doesn't have a sync operation, but later processors do.
            #define __mips_sync()
         #else 
            // We assume GCC or compatible compiler here
            #define __mips_sync()          \
               __asm__ __volatile__ (      \
                  ".set push\n\t"          \
                  ".set noreorder\n\t"     \
                  ".set mips2\n\t"         \
                  "sync\n\t"               \
                  ".set pop"               \
                  : : : "memory")
         #endif

      #endif

   #endif // EA_PROCESSOR_R5900, etc.


#endif // EA_PROCESSOR_MIPS


#endif // EATHREAD_MIPS_EATHREAD_SYNC_MIPS_H








