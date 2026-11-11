///////////////////////////////////////////////////////////////////////////////
// PerfTestThread.h
//
// Copyright(c) 2014, Electronic Arts Inc. All rights reserved.
//
// Created by Carl Hyde
///////////////////////////////////////////////////////////////////////////////


#ifndef PERFTESTTHREAD_H
#define PERFTESTTHREAD_H

#include <eathread/eathread_thread.h>
#include <benchmarkenvironment/results.h>
#include <EAIO/EAFileStream.h>
#include <EAStdC/EASprintf.h>

typedef intptr_t(*ThreadEntryFunction)(void*);

void PerfTestThreadAtomic(benchmarkenvironment::Results &results, EA::IO::FileStream* pLogFileStream);
void PerfTestThreadSemaphore(benchmarkenvironment::Results &results, EA::IO::FileStream* pLogFileStream);

inline void WriteToLogFile(EA::IO::FileStream* pLogFile, const char* formatString, ...)
{
    const int kLogBufferSize = 256;
    char8_t buffer[kLogBufferSize];

    va_list arguments;
    va_start(arguments, formatString);

    int numCharsWritten = EA::StdC::Vsnprintf(buffer, kLogBufferSize, formatString, arguments);

    va_end(arguments);

    pLogFile->Write(buffer, numCharsWritten);
}

#endif